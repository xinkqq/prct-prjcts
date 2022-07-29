#include "Menu.h"

#define SUCCESSFULLY_REGISTERED 1
#define BOOST_CONNECTION_ERROR 2
#define SUCCESSFULLY_LOGGED 3
#define USER_EXIT 4
#ifndef SERVCLIENTAPPLIC_SESSION_H
#define SERVCLIENTAPPLIC_SESSION_H

#include "Global.h"

int Register(socket_ptr socket);
int LogIn(socket_ptr socket);
bool CheckBack(char *);
int Session(socket_ptr socket);
void ShowBooksData(socket_ptr socket);

#endif //SERVCLIENTAPPLIC_SESSION_H
