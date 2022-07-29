//
// Created by xink on 6.04.22.
//
#include "ClientSession.h"
#ifndef SERVCLIENTAPPLIC_SERVER_H
#define SERVCLIENTAPPLIC_SERVER_H

class Server{
private:
    boost :: shared_ptr<bool> isRunning;
    boost :: shared_ptr<std :: vector<boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>> clients_sockets;
    boost :: shared_ptr<int> value_of_connections;
    boost :: shared_ptr<boost::thread> this_thread;
    boost :: shared_ptr<boost :: thread_group> server_threads;
    boost :: shared_ptr<boost :: asio :: ip :: tcp :: endpoint> serverAddress;
    boost :: shared_ptr<std :: vector<Client>> logged_clients;
    boost :: shared_ptr<int> value_of_logged_clients;
public:
    explicit Server(boost :: asio :: ip :: address,int);
    explicit Server(const Server &serv);
    ~Server();
    int Start();
    int Stop();
    void AddLoggedClient();
    int Monitor();
    int Accept();
};

#endif //SERVCLIENTAPPLIC_SERVER_H
