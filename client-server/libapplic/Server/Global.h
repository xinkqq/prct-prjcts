//
// Created by xink on 31.03.22.
//
#pragma once
#include "fort.hpp"
#include "Sha256.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <prepared_statement.h>
#include "Client.h"
#include "Order.h"
#include "Book.h"
#include "Person.h"
#include "Author.h"

#define LOCAL_HOST "127.0.0.1"
#define PORT 2001
#define DATABASE_ADDRESS "tcp://127.0.0.1:3306"
#define USERNAME "root"
#define PASSWORD "N2jjeh3aj752a3ec"

#define SQL_SUCCESSFULLY_LOGGED 1
#define SQL_CANT_LOGGED 2
#define SQL_ERROR 3
#define SQL_SUCCESSFULLY_ADDED 4
#define SQL_LOGIN_EXISTS 5
#define SQL_LOGIN_IS_NOT_EXISTS 6
#define BOOST_CONNECTION_ERROR 7
#define BOOST_THREAD_COMPLETE 8
#define SERV_SUCCESSFULLY_STARTED 9
#define SERV_START_ERROR 11
#define SERV_ACCEPT_ERROR 12
#define SERV_USER_EXIT 13
#define SERV_STOPPED 14
#define SERV_STOP_ERROR 15
#define USER_BACK 16
#define SORT_SUCCESS 17
#define USER_LOGGED_OUT 18

typedef boost :: shared_ptr<boost :: asio :: ip :: tcp :: socket> socket_ptr;

using std :: cout, std :: cin, std :: cerr,std :: endl;


static boost :: mutex mutex;
static std :: vector<Client> clients;
static std :: vector<socket_ptr> connections;

#ifndef SERVCLIENTAPPLIC_INCLUDE_H
#define SERVCLIENTAPPLIC_INCLUDE_H

#endif //SERVCLIENTAPPLIC_INCLUDE_H
