#include "User.h"

void User::setLogin(std::string& login)
{
    login_ = login;
}

void User::setName(std::string& name)
{
    name_ = name;
}

int User::getID()
{
    return id_;
}

std::string const& User::getLogin()
{
    return login_;
}

std::string const& User::getPassHash()
{
    return passHash_;
}

std::string const& User::getPassSalt()
{
    return passSalt_;
}

std::string const& User::getName()
{
    return name_;
}
