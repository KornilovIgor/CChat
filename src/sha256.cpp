#include "sha256.h"

std::string sha256::sha256_salt(const std::string& password, const std::string& salt)
{
    std::string saltedPassword = password + salt;

    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    if ((md = EVP_get_digestbyname("sha256")) == nullptr)
    {
        // Error handling
        return "";
    }

    if ((mdctx = EVP_MD_CTX_new()) == nullptr)
    {
        // Error handling
        return "";
    }

    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1)
    {
        // Error handling
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    if (EVP_DigestUpdate(mdctx, saltedPassword.c_str(), saltedPassword.size()) != 1)
    {
        // Error handling
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1)
    {
        // Error handling
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    EVP_MD_CTX_free(mdctx);

    std::string hashedPassword(hash, hash + hash_len);

    return hashedPassword;
}

std::string sha256::generate_salt()
{
    const int salt_length = 16;
    unsigned char salt[salt_length];

    if (RAND_bytes(salt, salt_length) != 1)
    {

        return "";
    }

    std::string base64_salt;
    base64_salt.resize(salt_length * 2);
    EVP_EncodeBlock((unsigned char*)&base64_salt[0], salt, salt_length);

    return base64_salt;
}
