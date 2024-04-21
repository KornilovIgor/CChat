#pragma once

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <string>

class sha256
{
public:
    std::string generate_salt();
    std::string sha256_salt(const std::string& password, const std::string& salt);
};