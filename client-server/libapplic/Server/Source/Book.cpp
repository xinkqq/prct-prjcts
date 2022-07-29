//
// Created by xink on 20.04.22.
//

#include "../Book.h"

Book :: Book(){
    this->id = boost :: shared_ptr<int>(new int);
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->author = boost :: shared_ptr<Author>(new Author);
}

Book :: Book(int id, std :: string name,Author author){
    this->id = boost :: shared_ptr<int>(new int);
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->author = boost :: shared_ptr<Author>(new Author(author));
    *this->id = id;
    *this->name = std :: move(name);
}

Book :: Book(const Book &book){
    this->id = boost :: shared_ptr<int>(new int);
    this->name = boost :: shared_ptr<std :: string>(new std :: string);
    this->author = boost :: shared_ptr<Author>(new Author(*book.author));
    *this->id = *book.id;
    *this->name = *book.name;
}

Book :: Book(const Book &&book){
    this->id = book.id;
    this->name = book.name;
    this->author = book.author;
}

Book :: ~Book(){
    std :: cout << "Book constructor" << std :: endl;
}