//
// Created by xink on 31.03.22.
//
#pragma once
#include "Person.h"
#ifndef SERVCLIENTAPPLIC_CLIENT_H
#define SERVCLIENTAPPLIC_CLIENT_H


class Client : public Person{
protected:
    boost :: shared_ptr<int> ID;
    boost :: shared_ptr<std :: string> login;
    boost :: shared_ptr<std :: string> password;
public:
    explicit Client(int ID,std :: string,std :: string ,std :: string,std :: string);
    virtual void PrintInfo() override;
    int GetId(){
        return *ID;
    }
    std :: string GetLogin() const{
        return *login;
    }
    std :: string GetPassword() const{
        return *password;
    }
    Client();
    Client(const Client &client_obj);
    ~Client();
};

#endif //SERVCLIENTAPPLIC_CLIENT_H
