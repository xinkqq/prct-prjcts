#include "Session.h"


int main() {
    boost :: asio :: io_service io_service;
    boost :: system :: error_code ec;
    boost :: asio :: ip :: tcp :: endpoint ep(boost :: asio :: ip :: address ::from_string(LOCAL_HOST),PORT);
    socket_ptr socket(new boost :: asio :: ip :: tcp :: socket(io_service));
    try {
        socket->connect(ep, ec);
        while(true) {
            if (Session(socket) == SUCCESSFULLY_LOGGED) {
                cout << "You successfully logged in\n";
                char id_buffer[30];
                if(UserMenu(socket) == USER_BACK){
                    continue;
                }else if(UserMenu(socket) == USER_EXIT){
                    exit(0);
                };
            }
        }
    }
    catch(const std :: exception &ex){
        cout << ex.what() << endl;
        cerr << "Error" << endl;
    }
}
