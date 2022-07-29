//
// Created by xink on 20.04.22.
//

#ifndef SERVCLIENTAPPLIC_GLOBAL_H
#define SERVCLIENTAPPLIC_GLOBAL_H
#pragma once
#include "fort.hpp"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "../Server/Client.h"

#define LOCAL_HOST "127.0.0.1"
#define PORT 2001
#define EXIT_STATUS 0
#define USER_EXIT 8
#define USER_BACK 16


typedef boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket> socket_ptr;
using std :: cout , std :: cin , std :: endl,std :: cerr;


#endif //SERVCLIENTAPPLIC_GLOBAL_H
