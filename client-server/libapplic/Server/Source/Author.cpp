//
// Created by xink on 20.04.22.
//

#include "../Author.h"


Author :: Author() : Person() {
    this->value_of_books = boost :: shared_ptr<int>(new int);
    this->writing_language = boost :: shared_ptr<std :: string>(new std :: string);
}

Author ::Author(std :: string name,std :: string surname,int value_of_books,std :: string writing_language) : Person(name,surname){
    this->value_of_books = boost :: shared_ptr<int>(new int);
    this->writing_language = boost :: shared_ptr<std :: string>(new std :: string);
    *this->value_of_books = value_of_books;
    *this->writing_language = std :: move(writing_language);
}

Author :: Author(const Author &&auth) noexcept{
    this->name  = auth.name;
    this->surname = auth.surname;
    this->value_of_books = auth.value_of_books;
    this->writing_language = auth.writing_language;
}

Author ::Author(const Author &auth) : Person(auth){
    this->value_of_books = boost :: shared_ptr<int>(new int);
    this->writing_language = boost :: shared_ptr<std :: string>(new std :: string);
    *this->value_of_books = *auth.value_of_books;
    *this->writing_language = *auth.writing_language;
}
Author :: ~Author() {
    std :: cout << "Author destructor\n";
}

void Author::PrintInfo() {
    std :: cout << *name <<  " " << *surname << " " << *value_of_books << " " << *writing_language << std :: endl;
}

