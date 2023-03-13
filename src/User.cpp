#include "User.h"

void User::setLogin(std::string& login)
{
    _login = login;
}

void User::setPassword(std::string& login)
{
    _login = login;
}

void User::setName(std::string& name)
{
    _name = name;
}

std::string const &User::getLogin()
{
    return _login;
}

std::string const& User::getPassword()
{
    return _password;
}

std::string const& User::getName()
{
    return _name;
}
