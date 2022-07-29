//
// Created by xink on 20.05.22.
//

#ifndef SERVCLIENTAPPLIC_SHA256_H
#define SERVCLIENTAPPLIC_SHA256_H

#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <string>
#include <openssl/sha.h>

namespace hash {
    std::string sha256(const std::string &password);
}
#endif //SERVCLIENTAPPLIC_SHA256_H
