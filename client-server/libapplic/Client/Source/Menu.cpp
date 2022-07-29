//
// Created by xink on 20.04.22.
//
#include "../Menu.h"


template<class T>
T Rtr(){
    T obj;
    cin >> obj;
    return obj;
}

void ShowBooksData(socket_ptr socket,char *size){
    char id[20],book_name[20],author_name[20],author_surname[20];
    fort :: char_table table;
    table << fort :: header << "BOOK ID" << "BOOK NAME" << "AUTHOR NAME" << "AUTHOR SURNAME" << fort :: endr;
    table.set_border_style(FT_NICE_STYLE);
    table.row(0).set_cell_content_fg_color(fort :: color :: green);
    for(int i = 0;i < atoi(size);i++){
        socket->receive(boost :: asio :: buffer(id));
        socket->receive(boost :: asio :: buffer(book_name));
        socket->receive(boost :: asio :: buffer(author_name));
        socket->receive(boost :: asio :: buffer(author_surname));
        table << id << book_name << author_name << author_surname << fort :: endr;
    }
    std :: cout << table.to_string() << std :: endl;
}

int LogMenu(){
    cout << "1.Register" << endl;
    cout << "2.Login" << endl;
    cout << "3.Exit" << endl;
    int choice;
    cin >> choice;
    return choice;
}

int UserMenu(socket_ptr socket){
    try {
        while (true) {
            cout << "1.Get info" << endl;
            cout << "2.Get books info" << endl;
            cout << "3.Order a book" << endl;
            cout << "4.Check orders" << endl;
            cout << "5.Log out" << endl;
            cout << "6.Exit" << endl;
            switch (auto choice = Rtr<int>();choice) {
                case 1 :;
                    {
                        system("clear");
                        char req[2] = {"1"};
                        socket->send(boost :: asio :: buffer(req));
                        char id[20], name[20], surname[20], login[20];
                        socket->receive(boost::asio::buffer(id));
                        socket->receive(boost::asio::buffer(name));
                        socket->receive(boost::asio::buffer(surname));
                        socket->receive(boost::asio::buffer(login));
                        std :: cout << "ID:" << id << "\nName:" << name << "\nSurname:" << surname << "\nLogin:" << login << std :: endl;
                    }
                    break;
                case 2 : ;
                    {
                        system("clear");
                        char req[2] = {"2"};
                        socket->send(boost :: asio :: buffer(req));
                        char size[20];
                        socket->receive(boost :: asio :: buffer(size));
                        if(atoi(size) == 1){
                            char ans[20];
                            socket->receive(boost :: asio :: buffer(ans));
                            if(ans == "err"){
                                cout << "Error,there is no books in DB" << endl;
                                continue;
                            }
                        }
                        ShowBooksData(socket,size);
                        cout << "1.Sort by..." << endl;
                        cout << "2.Go back\n>";
                        switch(auto chs = Rtr<int>();chs){
                            case 1 : ;
                                {
                                    system("clear");
                                    char rq[2] = {"1"};
                                    socket->send(boost :: asio :: buffer(rq));
                                    cout << "1.Sort by book name" << endl;
                                    cout << "2.Sort by author name" << endl;
                                    cout << "3.Sort by author surname\n>";
                                    switch(auto sort_choice = Rtr<int>();sort_choice){
                                        case 1 : ;
                                            {
                                                system("clear");
                                                char rq_st[2] = {"1"};
                                                socket->send(boost :: asio :: buffer(rq_st));
                                                ShowBooksData(socket,size);
                                            }
                                            break;
                                        case 2 : ;
                                            {
                                                system("clear");
                                                char rq_st[2] = {"2"};
                                                socket->send(boost :: asio :: buffer(rq_st));
                                                ShowBooksData(socket,size);
                                            }
                                            break;
                                        case 3 : ;
                                            {
                                                system("clear");
                                                char rq_st[2] = {"3"};
                                                socket->send(boost :: asio :: buffer(rq_st));
                                                ShowBooksData(socket,size);
                                            }
                                            break;
                                        default: ;
                                            {
                                            }
                                            break;
                                    }
                                }
                                break;
                            case 2 : ;
                                {
                                    system("clear");
                                    char rq[2] = {"2"};
                                    socket->send(boost :: asio :: buffer(rq));
                                    continue;
                                }
                                break;
                        }
                    }
                    break;
                case 3 : ;
                    {
                        char rq[2] = {"3"};
                        socket->send(boost :: asio :: buffer(rq));
                        cout << "Enter the id of the book,that you want to order(b)" << endl;
                        char id[3];
                        cin >> id;
                        socket->send(boost :: asio :: buffer(id));
                        char resp[3];
                        socket->receive(boost :: asio :: buffer(resp));
                        switch(resp[0]){
                            case '1' : ;
                                {
                                    cout << "Book that you want to order:" << endl;
                                    char bk_id[20],bk_name[20],auth_name[20],auth_surname[20];
                                    socket->receive(boost :: asio :: buffer(bk_id));
                                    socket->receive(boost :: asio :: buffer(bk_name));
                                    socket->receive(boost :: asio :: buffer(auth_name));
                                    socket->receive(boost :: asio :: buffer(auth_surname));
                                    cout << "Book name:" << bk_name << endl << "Author name:" << auth_name << endl <<
                                    "Author surname:" << auth_surname << endl;
                                    std :: cout << "Do you want to order this book?(y/n)" << std :: endl;
                                    char ch;
                                    std :: cin >> ch;
                                    if(ch == 'Y' || ch ==  'y'){
                                        char buff[3] {"y"};
                                        socket->send(boost :: asio :: buffer(buff));
                                        char resp_buffer[3];
                                        socket->receive(boost :: asio :: buffer(resp_buffer));
                                        if(resp_buffer[0] == '1'){
                                            std :: cout << "Order has been successfully added\n";
                                        }
                                        else if(resp_buffer[0] == '2'){
                                            std :: cout << "Can't add order, problems with data base\n";
                                        }
                                    }
                                    else{
                                        char buff[3] {"n"};
                                        socket->send(boost :: asio :: buffer(buff));
                                        std :: cout << "Order has been declined\n";
                                    }
                                }
                                break;
                            case '2' : ;
                                {
                                    cout << "There is no book with this id,please try again\n" << endl;
                                }
                                break;
                            default : ;
                                {

                                }
                                break;
                        }
                    }
                    break;
                case 4 : ;
                    {
                        char req[3] = {"4"};
                        socket->send(boost :: asio :: buffer(req));
                        char size_of_orders[32];
                        socket->receive(boost :: asio :: buffer(size_of_orders));
                        if(size_of_orders[0] == '0'){
                            std :: cout << "You have no orders\n";
                            break;
                        }
                        else{
                            std :: cout << "YOUR ORDERS:" << std :: endl;
                            fort :: char_table table;
                            table.set_border_style(FT_DOUBLE2_STYLE);
                            table.column(0).set_cell_text_align(fort::text_align::center);
                            table.column(1).set_cell_text_align(fort::text_align::center);
                            table.column(2).set_cell_text_align(fort::text_align::center);
                            table.column(3).set_cell_text_align(fort::text_align::center);
                            table.row(0).set_cell_content_fg_color(fort :: color :: red);
                            table << fort :: header << "BOOK ID" << "BOOK_NAME" << "AUTHOR_NAME" << "AUTHOR_SURNAME" << fort :: endr;
                            for(int i = 0;i < atoi(size_of_orders);i++){
                                char book_id[64];
                                char book_name[64];
                                char author_name[64];
                                char author_surname[64];
                                socket->receive(boost :: asio :: buffer(book_id));
                                socket->receive(boost :: asio :: buffer(book_name));
                                socket->receive(boost :: asio :: buffer(author_name));
                                socket->receive(boost :: asio :: buffer(author_surname));
                                table << book_id << book_name << author_name << author_surname << fort :: endr;
                            }
                            std :: cout << table.to_string() << std :: endl;
                        }
                    }
                    break;
                case 5 : ;
                    {
                        char req[3] = {"5"};
                        socket->send(boost :: asio :: buffer(req));
                        return USER_BACK;
                    }
                    break;
                case 6 : ;
                    {
                        char req[3] = {"6"};
                        socket->send(boost :: asio :: buffer(req));
                        exit(0);
                    }
                    break;
            }
        }
    }catch(std :: exception &exc){
        cout << "Exception\n";
    }
    catch(boost :: system :: error_code &ec){
        cout << "Error code:" << ec.message() << endl;
    }
}
