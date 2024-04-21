#pragma once

#include <string>

class User
{
	int id_;
	std::string login_;
	std::string passHash_;
	std::string passSalt_;
	std::string name_;

public:
	User(int id, const std::string& login, const std::string& passHash,  const std::string& passHashSalt, const std::string& name):
	id_(id), login_(login), passHash_(passHash), passSalt_(passHashSalt), name_(name)
	{};

	void setLogin(std::string& login);
	void setName(std::string& name);

	int getID();
	std::string const& getLogin();
	std::string const& getPassHash();
	std::string const& getPassSalt();
	std::string const& getName();
};
