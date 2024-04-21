#include "Chat.h"

#include <iostream>
#include <algorithm>
#include <limits>

#ifdef _WIN32
    const std::string clearCommand = "cls";  // for Windows
#else
    const std::string clearCommand = "clear";  // for not Windows
#endif

void Chat::run()
{
	menuStart();
}

void Chat::menuStart()
{
	while (true)
	{
		printStartMenu();
		int input = inputMenu(2);
		switch (input)
		{
		case 1:
			signIn();
			break;
		case 2:
			signUp();
			break;
		case 0:
			return;
		default:
			continue;
		}
	}
}

void Chat::menuMain()
{
	while (true)
	{
		printUserMenu();
		int input = inputMenu(3);
		switch (input)
		{
		case 1:
			showMessages();
			break;
		case 2:
			sendPrivateMessage();
			break;
		case 3:
			sendPublicMessage();
			break;
		case 0:
			_currentUser = nullptr;
			return;
		default:
			break;
		}
	}
}

const std::shared_ptr<User> Chat::getUserByLogin(std::string &login) const
{
    for (auto &user : users_)
    {
        if (login == user->getLogin())
        {
            return user;
        }
    }
    return nullptr;
}

void Chat::addUser(std::string& login, std::string& password, std::string& name)
{
	sha256 sha256;
	std::string salt = sha256.generate_salt();
	std::string hashedPassword = sha256.sha256_salt(password, salt);
    _currentUser = std::make_shared<User>(usersCount_, login, hashedPassword, salt, name);
    users_.push_back(_currentUser);
	++usersCount_;
}

void Chat::addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string &text)
{
	messages_.push_back(std::make_unique<Message>(to, from, text));
}

void Chat::signUp()
{
	std::string login;
	while (true)
	{
		std::cout << "Input login > ";
		getline(std::cin, login);
		if (isValidLogin(login) == true)
		{
			if (getUserByLogin(login) == nullptr)
			{
				break;
			}
			else
			{
				std::cout << "That login is taken.";
				waitForInput();
			};
		}
		else
		{
			std::cout << "Incorrect login. Use only [1..0, a..Z, !..`] Size: 1-16" << std::endl;
			waitForInput();
		}

		if (repeat() == false)
		{
			return;
		}
	}

	std::string password;
	std::string passwordRetype;
	while (true)
	{
		std::cout << "Input password > ";
		getline(std::cin, password);
		if (isValidPassword(password) == false)
		{
			std::cout << "Incorrect password. Use only [1..0, a..Z]. Size: 8-128" << std::endl;
			waitForInput();
		}
		else
		{
			std::cout << "Retype password > ";
			getline(std::cin, passwordRetype);
			if (password == passwordRetype)
			{
				break;
			}
			else
			{
				std::cout << "Passwords don't match." << std::endl << std::endl;
				waitForInput();
				if (repeat() == false)
				{
					return;
				}
			}
		}
	}

	std::string name;
	std::cout << "Input name > ";
	getline(std::cin, name);

	addUser(login, password, name);
	std::cout << "The user has been successfully created" << std::endl << std::endl;
	waitForInput();
}

void Chat::signIn()
{
	std::string login;
	std::cout << "Input login > ";
	getline(std::cin, login);

	_currentUser = getUserByLogin(login);
	if (_currentUser == nullptr)
	{
		std::cout << "Login not found." << std::endl << std::endl;
		waitForInput();
		return;
	}

	std::string password;
	sha256 sha256;
	std::cout << "Input password > ";
	getline(std::cin, password);
	if (_currentUser->getPassHash() == sha256.sha256_salt(password, _currentUser->getPassSalt()))
	{
		std::cout << std::endl << "Welcome to CChat,  " << _currentUser->getName() << "!" << std::endl << std::endl;
		waitForInput();
		menuMain();
	}
	else
	{
		_currentUser = nullptr;
		std::cout << "Wrong password!";
		waitForInput();
		return;
	}
}

void Chat::showMessages()
{
	if (messages_.empty())
	{
		std::cout << "No messages" << std::endl;
		waitForInput();
		return;
	}

	int countPrintMessages{ 0 };
	for (auto &message : messages_)
	{
		if ((message->getTo() == _currentUser) || (message->getTo() == nullptr) || (message->getFrom() == _currentUser))
			{
				printMessage(message);
				++countPrintMessages;
			}
	}

	if (countPrintMessages == 0)
	{
		std::cout << "No messages" << std::endl;
	}

	waitForInput();
}

void Chat::printMessage(const std::unique_ptr<Message>& message) const
{
	if (message->getFrom() == _currentUser)
	{
		std::cout << "Me ";
	}
	else
	{
		std::cout << message->getFrom()->getName() << " (" << message->getFrom()->getLogin() << ") ";
	}

	if (message->getTo() == _currentUser)
	{
		std::cout << "to me: ";
	}
	else if (message->getTo() != nullptr)
	{
		std::cout << "to " << message->getTo()->getName() << " (" << message->getTo()->getLogin() << "): ";
	}
	else
	{
		std::cout << "to all: ";
	}

	std::cout << message->getText() << std::endl;
}

void Chat::sendPrivateMessage()
{
	std::string login;
	std::cout << "Input login \"To\"> ";
	getline(std::cin, login);

	std::shared_ptr<User> to = getUserByLogin(login);
	if (to == nullptr)
	{
		std::cout << "Login not found." << std::endl;
		waitForInput();
		return;
	}
	else
	{
		std::string text;
		std::cout << "Input message > ";
		getline(std::cin, text);
		addMessage(to, _currentUser, text);
		std::cout << std::endl << "The message has been sent." << std::endl;
		waitForInput();
	}
}

void Chat::sendPublicMessage()
{
	std::string text;
	std::cout << "Input message > ";
	getline(std::cin, text);
	addMessage(nullptr, _currentUser, text);
	std::cout << std::endl << "The message has been sent." << std::endl;
	waitForInput();
}

void Chat::printStartMenu()
{
	system(clearCommand.c_str());
	std::cout << "CChat:Start menu" << std::endl;
	std::cout << "1 - SignIn" << std::endl;
	std::cout << "2 - SignUp" << std::endl;
	std::cout << "0 - Exit" << std::endl;
	std::cout << std::endl;
}

void Chat::printUserMenu()
{
	system(clearCommand.c_str());
	std::cout << "CChat:User menu" << std::endl;
	std::cout << "1 - Show messages" << std::endl;
	std::cout << "2 - Send private message" << std::endl;
	std::cout << "3 - Send public message" << std::endl;
	std::cout << "0 - Logout" << std::endl;
	std::cout << std::endl;
}

int Chat::inputMenu(int count)
{
	int input = -1;
	std::cout << "Input > ";
	std::cin >> input;
	if (std::cin.fail() || std::cin.get() != '\n')
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cerr << "Input error: Invalid input item menu" << std::endl << std::endl;
		waitForInput();
		return -1;
	}
	else if (input < 0 || input > count)
	{
		std::cout << "Input error: A non-existent menu item is selected." << std::endl << std::endl;
		waitForInput();
		return -1;
	}
	std::cout << std::endl;
	return input;
}

bool Chat::isValidLogin(const std::string& login ) const
{
	if (login.length() < 1 || login.length() > 16)
	{
		return false;
	}

	for (char ch : login)
	{
		if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Chat::isValidPassword(const std::string& password) const
{
	if (password.length() < 8 || password.length() > 128)
	{
		return false;
	}

	if (std::any_of (password.begin(), password.end(), [](char ch) {return ch < 33 || ch > 122;}))
    {
		return false;
	}

	return true;
}

bool Chat::repeat()
{
	while (true)
	{
		std::cout << std::endl;
		std::cout << "1 - try again" << std::endl;
		std::cout << "0 - return" << std::endl;
		int input = inputMenu(1);
		switch (input)
		{
		case 1:
			return true;
		case 0:
			return false;
		default:
			continue;
		}
	}
}

void Chat::waitForInput()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
