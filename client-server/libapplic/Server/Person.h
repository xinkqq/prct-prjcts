//
// Created by xink on 8.04.22.
//
#pragma once
#ifndef SERVCLIENTAPPLIC_PERSON_H
#define SERVCLIENTAPPLIC_PERSON_H
#include <boost/shared_ptr.hpp>
#include <string>
#include <iostream>

class Person{
protected:
    boost :: shared_ptr<std :: string> name;
    boost :: shared_ptr<std :: string> surname;
public:
    explicit Person(std :: string,std :: string);
    virtual void PrintInfo() = 0;
    std :: string GetName() const{
        return* name;
    }
    std :: string GetSurname() const{
        return *surname;
    }
    Person();
    explicit Person(const Person&);
    virtual ~Person();
};

#endif //SERVCLIENTAPPLIC_PERSON_H
