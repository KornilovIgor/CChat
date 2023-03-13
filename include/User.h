#pragma once

#include <string>

class User
{
	std::string _login;
	std::string _password;
	std::string _name;

public:
	User(std::string login, std::string password, std::string name):
	_login(login), _password(password), _name(name)
	{};
	
	void setLogin(std::string& login);
	void setPassword(std::string& login);
	void setName(std::string& name);

	std::string const& getLogin();
	std::string const& getPassword();
	std::string const& getName();
};