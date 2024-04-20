#pragma once

#include "Message.h"

#include <vector>
#include <memory>

class Chat
{
	std::vector <std::shared_ptr<User>> _users;
	std::vector <std::unique_ptr<Message>> _messages;

	std::shared_ptr<User> _currentUser = nullptr;

	void menuStart();
	void menuMain();

	const std::shared_ptr<User> getUserByLogin(std::string& login) const;

	void addUser(std::string& login, std::string& password, std::string& name);
	void addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string& text);

	void signUp();
	void signIn();

	void showMessages();
	void printMessage(const std::unique_ptr<Message>& Message) const;

	void sendPrivateMessage();
	void sendPublicMessage();

	void printStartMenu();
	void printUserMenu();
	int inputMenu(int countMenuItem);

	bool isValidLogin(const std::string& login) const;
	bool isValidPassword(const std::string& password) const;

	bool repeat();
	void waitForInput();

public:
	void run();
};
