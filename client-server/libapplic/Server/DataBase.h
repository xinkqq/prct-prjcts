//
// Created by xink on 31.03.22.
//
#include "Global.h"
#include "Buffs.h"

namespace DataBase {
    int AddNewUser(const std::string &name, const std::string &surname, const std::string &login,
                   const std::string &password);

    int GetBooksValue(sql::Statement *stmt);

    int GetOrdersValue(sql::Statement *stmt);

    int GetUsersValue(sql::Statement *stmt);

    LogFlagReturning CheckLoginPassword(std::string input_login, std::string input_password);

    int CheckLogin(std::string input_login);

    std::map<int, BookInfo> BooksMap();

    int AddNewBook(std::string name, Author author);

    int AddNewOrder(Order &order);

    std :: vector<OrderInfo> GetOrders(Client);
}

#ifndef SERVCLIENTAPPLIC_DATABASE_H
#define SERVCLIENTAPPLIC_DATABASE_H

#endif //SERVCLIENTAPPLIC_DATABASE_H
