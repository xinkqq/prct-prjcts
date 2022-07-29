//
// Created by xink on 20.04.22.
//

#include "../Server.h"

Server :: Server(boost :: asio :: ip :: address servIP,int port){
    try{
        this->value_of_logged_clients = boost :: shared_ptr<int>(new int);
        *this->value_of_logged_clients = 0;
        this->logged_clients = boost :: shared_ptr<std :: vector<Client>>(new std :: vector<Client>);
        this->isRunning = boost :: shared_ptr<bool>(new bool);
        *this->isRunning = false;
        this->value_of_connections = boost :: shared_ptr<int>(new int);
        this->clients_sockets = boost :: shared_ptr<std :: vector<boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>>(new std :: vector<boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>);
        this->server_threads = boost::shared_ptr<boost::thread_group>(new boost::thread_group);
        this->serverAddress = boost::shared_ptr<boost::asio::ip::tcp::endpoint>(
                new boost::asio::ip::tcp::endpoint(servIP, port));
    }
    catch(boost :: system :: error_code &err_c){
        cout << "Error,error_code:" << err_c.message() << endl;
    }
}
//Copy constructor of server can not connect to clients that are working with the first server,
// so new server just copying address of the previous server,but it has new port,which is more than previous by 1

Server :: Server(const Server &serv){
    this->value_of_logged_clients = boost :: shared_ptr<int>(new int);
    *this->value_of_logged_clients = 0;
    this->logged_clients = boost :: shared_ptr<std :: vector<Client>>(new std :: vector<Client>);
    this->value_of_connections = boost :: shared_ptr<int>(new int);
    this->isRunning = boost :: shared_ptr<bool>(new bool);
    *this->isRunning = false;
    this->clients_sockets = boost :: shared_ptr<std :: vector<boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>>(new std :: vector<boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>);
    this->server_threads = boost :: shared_ptr<boost :: thread_group>(new boost :: thread_group);
    this->serverAddress = boost :: shared_ptr<boost :: asio :: ip :: tcp :: endpoint>(new boost :: asio :: ip :: tcp :: endpoint(serv.serverAddress->address(),serv.serverAddress->port() + 1));
}

Server ::~Server() {
    *value_of_connections = 0;
    clients_sockets->clear();
    cout << "Server has been deleted\n" << endl;
}

int Server :: Start() {
    try {
        *this->isRunning = true;
        cout << "Server has been started" << endl;
        *this->value_of_connections = 0;
        this->this_thread = boost::shared_ptr<boost::thread>(new boost::thread([this] { Accept(); }));
    }
    catch(std :: exception &ex){
        cout << "Error" << std :: endl;
        return SERV_START_ERROR;
    }
    return SERV_SUCCESSFULLY_STARTED;
}

int Server :: Stop(){
    try{
        *this->isRunning = false;
        this->server_threads->interrupt_all();
        this->this_thread->interrupt();
        return SERV_STOPPED;
    }
    catch(std :: exception &ex){
        cout << "Error in server interruption" << std :: endl;
        return SERV_STOP_ERROR;
    }
}

int Server :: Accept() {
    try{
        std :: cout << "Server is working now\n" << std :: endl;
        boost :: asio :: io_service io_service;
        boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor(
                new boost::asio::ip::tcp::acceptor(io_service, *serverAddress));
        while (true) {
            boost::shared_ptr<boost::asio::ip::tcp::socket> socket(new boost::asio::ip::tcp::socket(io_service));
            acceptor->accept(*socket);
            clients_sockets->push_back(socket);
            *value_of_connections = *value_of_connections + 1;
            server_threads->create_thread([socket, this, capture0 = clients_sockets->size()] { return ClientSession(socket, clients_sockets, capture0, logged_clients, value_of_logged_clients); });
        }
    }catch(boost :: system :: error_code &ec){
        return SERV_USER_EXIT;
    }catch(std :: exception &ex){
        return SERV_USER_EXIT;
    }
}

int Server :: Monitor(){
    try{
        while(*isRunning) {
            cout << "CONNECTED USERS TO THE SERVER:" << clients_sockets->size() << endl;
            fort :: char_table table;
            table.set_border_style(FT_DOUBLE2_STYLE);
            table.column(0).set_cell_text_align(fort::text_align::center);
            table.column(1).set_cell_text_align(fort::text_align::center);
            table.column(2).set_cell_text_align(fort::text_align::center);
            table.column(3).set_cell_text_align(fort::text_align::center);
            table.row(0).set_cell_content_fg_color(fort :: color :: red);
            table << fort :: header << "ID" << "NAME" << "SURNAME" << "LOGIN" << fort :: endr;
            for(int i = 0;i < logged_clients->size();i++){
                table << logged_clients->at(i).GetId() << logged_clients->at(i).GetName() << logged_clients->at(i).GetSurname()
                << logged_clients->at(i).GetLogin()  << fort :: endr;
            }
            std :: cout << table.to_string() << std :: endl;
            boost :: this_thread ::sleep(boost :: posix_time:: seconds(2));
            system("clear");
        }
        std :: cout << "Server has been stopped,can not monitor this server\n";
    }
    catch(boost :: system :: error_code &ec){
        cout << "Error, cant monitor this server" << ec.message() << endl;
        return BOOST_CONNECTION_ERROR;
    }
    catch(std :: exception &exc){
        cout << "Error, cant monitor this server" << exc.what() << endl;

    }
    return SERV_STOPPED;
}
