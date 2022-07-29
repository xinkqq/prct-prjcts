//
// Created by xink on 20.05.22.
//
#include "../Sha256.h"

std :: string hash :: sha256(const std :: string &password){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);
    std :: stringstream stream;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        stream << std :: hex << std :: setw(2) << std :: setfill('0') << (int)hash[i];
    }
    return stream.str();
}