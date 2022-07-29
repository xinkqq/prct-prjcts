//
// Created by xink on 20.04.22.
//

#include "../Person.h"

Person :: Person(){
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->surname = boost :: shared_ptr<std :: string>(new std :: string);
}

Person ::Person(std :: string name,std :: string surname) {
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->surname = boost :: shared_ptr<std :: string>(new std :: string);
    *this->name = name;
    *this->surname = surname;
}
Person :: Person(const Person &pers){
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->surname = boost :: shared_ptr<std :: string>(new std :: string);
    *this->name = *pers.name;
    *this->surname = *pers.surname;
}
Person :: ~Person(){
    std :: cout << "Person destructor\n" << std :: endl;
}
