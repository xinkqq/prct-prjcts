#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <fstream>
#include <iterator>
#include <string>
#include <memory>


using std :: cout,std :: cin, std :: endl;
static boost :: mutex mutex;

int Session(std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> &socket);
void GetFilesNames(std :: shared_ptr<std :: vector<std :: string>> &source_arr);
int SendFile(std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> &socket,int &&id);
int main()
{
    system("chcp 65001");
    std :: shared_ptr<std :: vector<std :: shared_ptr<boost :: asio :: ip :: tcp :: socket>>> sockets(new std :: vector<std :: shared_ptr<boost :: asio :: ip ::tcp :: socket>>);
    std :: shared_ptr<boost :: thread_group> threads(new boost :: thread_group);
    boost :: asio :: io_service io_service;
    std :: shared_ptr<boost :: asio :: ip :: tcp :: endpoint> eP(new boost :: asio :: ip :: tcp :: endpoint(boost :: asio :: ip :: address ::from_string("127.0.0.1"),4000));
    std :: shared_ptr<boost :: asio :: ip :: tcp :: acceptor> acceptor(new boost :: asio :: ip :: tcp :: acceptor(io_service,*eP));
    while(true){
        std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> socket(new boost :: asio :: ip :: tcp :: socket(io_service));
        acceptor->accept(*socket);
        sockets->push_back(socket);
        threads->create_thread([&sockets]{ return Session(sockets->at(sockets->size() - 1));});
    }
    return 0;
}

int Session(std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> &socket){
    std :: shared_ptr<std :: vector<std :: string>> files_name(new std :: vector<std :: string>);
    GetFilesNames(files_name);

    char number_of_files[16];
    strcpy(number_of_files,std ::to_string(files_name->size()).c_str());
    socket->send(boost :: asio :: buffer(number_of_files));
    for(auto &i : *files_name){
        char file_name_size[16];
        strcpy(file_name_size,std ::to_string(i.size()).c_str());
        socket->send(boost :: asio :: buffer(file_name_size,16));
        socket->send(boost :: asio :: buffer(i.c_str(),strlen(i.c_str())));
    }
    char chs[4];
    socket->receive(boost :: asio :: buffer(chs));
    SendFile(socket,atoi(chs));
}


void GetFilesNames(std :: shared_ptr<std :: vector<std :: string>> &source_arr){
    boost :: filesystem :: path path_to_files("C:\\temp"); // Place where files are located
    for(auto &i : boost :: filesystem :: directory_iterator(path_to_files)){
        source_arr->push_back(i.path().filename().string());
    }
}

int SendFile(std :: shared_ptr<boost :: asio :: ip :: tcp :: socket> &socket,int &&id){
    boost :: filesystem :: path path_to_files("C:\\temp"); // Place where files are located
    int file_counter = 1;
    for(auto &i : boost :: filesystem :: directory_iterator(path_to_files)){
        if(id == file_counter){
            socket->send(boost :: asio :: buffer(std ::to_string(i.path().filename().string().size()).c_str(),16)); //sending info about size of file name
            socket->send(boost :: asio :: buffer(i.path().filename().string().c_str(),i.path().filename().string().size())); //sending file name
            int size_of_file = boost :: filesystem ::file_size(i.path().string());
            char *file_info = new char[size_of_file];
            mutex.lock();
            std :: fstream file_to_send;
            file_to_send.open(i.path().string(),std :: ios_base :: in | std :: ios :: binary);
            file_to_send.read(file_info,size_of_file);
            socket->send(boost :: asio :: buffer(std ::to_string(size_of_file).c_str(),16)); //sending info about file size
            socket->send(boost :: asio :: buffer(file_info,size_of_file)); // sending file
            file_to_send.close();
            delete[] file_info;
            mutex.unlock();
        }
        file_counter++;
    }
}





