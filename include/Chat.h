#pragma once

#include "Message.h"

#include <vector> 
#include <memory>

class Chat
{
protected:

	std::vector <std::shared_ptr<User>> _users; //Одним из юзеров владеет не только вектор, но и переменная _currentUser, поэтому выбрал shared
	std::vector <std::unique_ptr<Message>> _messages; 

	std::shared_ptr<User> _currentUser = nullptr;

public:
	void run();

	void menuStart();
	void menuMain();

	const std::shared_ptr<User> findUser(std::string &login) const;

	void addUser(std::string &login, std::string &password, std::string &name);
	void addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string &text);

	void signUp();
	void signIn();

	void showMessages();
	void printMessage(const std::unique_ptr<Message> &Message) const;
	
	void sendPrivateMessage();
	void sendPublicMessage();

	void printStartMenu();
	void printUserMenu();
	int inputMenu(int countMenuItem);

	bool isValidLogin(const std::string& login) const;
	bool isValidPassword(const std::string& password) const;

	void showUserByIndex();
	const std::shared_ptr<User> getUserByIndex(int index) const;

	bool repeat();
};