#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <fstream>
#include <string>


int ReceiveFile(std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> &socket);

int main()
{
    boost :: asio :: io_service io_service;
    std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> socket(new boost :: asio :: ip :: tcp :: socket(io_service));
    boost :: asio :: ip :: tcp :: endpoint ep(boost :: asio :: ip :: address ::from_string("127.0.0.1"),4000);
    socket->connect(ep);
    char number_of_files[16];
    socket->receive(boost :: asio :: buffer(number_of_files));
    for(int i = 0;i < atoi(number_of_files);i++){
        char file_name_size[16];
        socket->receive(boost :: asio :: buffer(file_name_size));
        char file_name[atoi(file_name_size)];
        socket->receive(boost :: asio :: buffer(file_name,atoi(file_name_size)));
        std :: cout << "ID: " << i + 1 << " File info: "<< file_name << " " <<  strlen(file_name) << std :: endl;
    }
    std :: cout << "Enter the file id that you want to download\n";
    char choice[4];
    std :: cin >> choice;
    socket->send(boost :: asio :: buffer(choice));
    ReceiveFile(socket);
}

int ReceiveFile(std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> &socket){
    char file_name_size_buffer[16];
    socket->receive(boost :: asio :: buffer(file_name_size_buffer));
    char file_name_buffer[atoi(file_name_size_buffer)];
    socket->receive(boost :: asio :: buffer(file_name_buffer,atoi(file_name_size_buffer)));
    char file_size_buffer[16];
    socket->receive(boost :: asio :: buffer(file_size_buffer));
    char *file = new char[atoi(file_size_buffer)];
    socket->receive(boost :: asio ::buffer(file,atoi(file_size_buffer)));
    std::ofstream receivedFile { std :: string(file_name_buffer) ,std :: ios_base :: out | std :: ios :: binary};
    receivedFile.write(file,atoi(file_size_buffer));
    receivedFile.close();
    delete[] file;
}

