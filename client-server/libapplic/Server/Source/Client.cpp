//
// Created by xink on 20.04.22.
//

#include "../Client.h"


Client ::Client() : Person(){
    this->ID = boost :: shared_ptr<int>(new int);
    this->login = boost :: shared_ptr<std :: string>(new std :: string);
    this->password = boost :: shared_ptr<std :: string>(new std :: string);
}
void Client ::PrintInfo() {
    std :: cout << "ID:" << *this->ID << "Name:" << *this->name << "Surname:"
                << *this->surname << "Login:" << *this->login;
}

Client :: Client(int ID,std :: string name,std :: string surname,std :: string login,std :: string password) : Person(name,surname){
    this->ID = boost::shared_ptr<int>(new int);
    this->login = boost::shared_ptr<std::string>(new std::string);
    this->password = boost::shared_ptr<std::string>(new std::string);
    *this->ID = ID;
    *this->login = std :: move(login);
    *this->password = std :: move(password);
}
Client :: Client(const Client &client) : Person(client){
    this->ID = boost::shared_ptr<int>(new int);
    this->login = boost::shared_ptr<std::string>(new std::string);
    this->password = boost::shared_ptr<std::string>(new std::string);
    *this->ID = *client.ID;
    *this->login = *client.login;
    *this->password = *client.password;
}
Client :: ~Client(){
    std :: cout << "Client destructor\n" << std::endl;
}