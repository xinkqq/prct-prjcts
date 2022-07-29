//
// Created by xink on 20.04.22.
//

#include "../Session.h"


int Session(socket_ptr socket){
    boost :: shared_ptr<bool> flag_ptr(new bool);
    *flag_ptr = true;
    while(*flag_ptr) {
        try {
            switch (auto choice = LogMenu();choice) {
                case 1 :;
                    {
                        char req[2] = {"1"};
                        socket->send(boost::asio::buffer(req));
                        int regFlag = Register(socket);
                        system("clear");
                        if (regFlag == SUCCESSFULLY_REGISTERED) {
                            cout << "U have been successfully registered, please log in\n";
                        }
                        else if(regFlag == USER_BACK){
                            cout << "Going back" << endl;
                        }
                    }
                    break;
                case 2 :;
                    {
                        char req[2] = {"2"};
                        socket->send(boost :: asio :: buffer(req));
                        int logFlag = LogIn(socket);
                        if(logFlag == SUCCESSFULLY_LOGGED){
                            return SUCCESSFULLY_LOGGED;
                        }
                        else if(logFlag == USER_BACK){
                            continue;
                        }
                    }
                    break;
                case 3 :;
                    {
                        char req[2] = {"3"};
                        socket->send(boost :: asio :: buffer(req));
                        exit(EXIT_STATUS);
                    }
                    break;
                case 4 :;
                    {
                        exit(EXIT_STATUS);
                    }
                default :;
                    {
                        exit(EXIT_STATUS);
                    }
            }
        }
        catch (std::exception &exc) {
            cout << "Error\n";
            return BOOST_CONNECTION_ERROR;
        }
    }
    return USER_EXIT;
}

int Register(socket_ptr socket) {
    char name[255], surname[255], login[255], password[255];
    cout << "Enter your name\n" << endl;
    cin >> name;
    socket->send(boost::asio::buffer(name));
    if(CheckBack(name)){
        cout << "Going back\n";
        return USER_BACK;
    }
    cout << "Enter your surname\n" << endl;
    cin >> surname;
    socket->send(boost::asio::buffer(surname));
    if(CheckBack(surname)){
        cout << "Going back\n";
        return USER_BACK;
    }
    cout << "Enter your login\n" << endl;
    cin >> login;
    socket->send(boost::asio::buffer(login));
    if(CheckBack(login)){
        cout << "Going back\n";
        return USER_BACK;
    }
    cout << "Enter your password\n" << endl;
    cin >> password;
    socket->send(boost::asio::buffer(password));
    if(CheckBack(password)){
        cout << "Going back\n";
        return USER_BACK;
    }
    char answ[2];
    socket->receive(boost::asio::buffer(answ));
    if (answ[0] == '1') {
        return SUCCESSFULLY_REGISTERED;
    } else if (answ[0] == '3') {
        cout << "Error, please try again" << endl;
        return Register(socket);
    } else if (answ[0] == '5') {
        cout << "This login already exists,try another one" << endl;
        return Register(socket);
    }
}

int LogIn(socket_ptr socket){
    char login[255];
    char password[255];
    cout << "Enter your login:" << endl;
    cin >> login;
    socket->send(boost::asio::buffer(login));
    if(CheckBack(login)){
        cout << "Going back\n";
        return USER_BACK;
    }
    cout << "Enter your password:" << endl;
    cin >> password;
    socket->send(boost::asio::buffer(password));
    if(CheckBack(password)){
        cout << "Going back\n";
        return USER_BACK;
    }
    char answ[2];
    socket->receive(boost::asio::buffer(answ));
    if (answ[0] == '1') {
        return SUCCESSFULLY_LOGGED;
    } else {
        cout << "Incorrect login or password\n";
        return LogIn(socket);
    }
}


bool CheckBack(char *buffer){
    if(strlen(buffer) == 1){
        if(buffer[0] == 'b' || buffer[0] == 'B'){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}


