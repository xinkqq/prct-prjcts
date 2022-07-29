//
// Created by xink on 31.03.22.
//
#ifndef SERVCLIENTAPPLIC_CLIENTSESSION_H
#define SERVCLIENTAPPLIC_CLIENTSESSION_H

#include "DataBase.h"
#include "Buffs.h"


int RegFunction(socket_ptr socket);
LogFlagReturning LogFunction(socket_ptr socket);
int UserMenu(Client client,socket_ptr);
int ClientSession(socket_ptr socket,boost :: shared_ptr<std :: vector<boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>> sockets,int this_socket_id,boost :: shared_ptr<std :: vector<Client>> clients,boost :: shared_ptr<int> value_of_logged_clients);
bool CheckBack(char *buffer);
int SortBy(socket_ptr socket,int sort_key,std :: map<int,BookInfo> &books);


#endif //SERVCLIENTAPPLIC_CLIENTSESSION_H