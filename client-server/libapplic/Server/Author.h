//
// Created by xink on 8.04.22.
//
#pragma once
#ifndef SERVCLIENTAPPLIC_AUTHOR_H
#define SERVCLIENTAPPLIC_AUTHOR_H


#include "Person.h"

class Author : public Person{
private:
    boost :: shared_ptr<int> value_of_books;
    boost :: shared_ptr<std :: string> writing_language;
public:
    explicit Author(std :: string,std :: string,int,std :: string);
    void PrintInfo() override;
    explicit Author(const Author &auth);
    Author(const Author &&auth) noexcept;
    std :: string GetLanguage() const{
        return *writing_language;
    }
    int GetBooksValue() const{
        return *value_of_books;
    }
    Author();
    ~Author();
};

#endif //SERVCLIENTAPPLIC_AUTHOR_H
