#include "Chat.h"

#include <iostream>

void Chat::run()
{
	menuStart();
}

void Chat::menuStart()
{
	int input = -1;
	while (true)
	{
		printStartMenu();
		input = inputMenu(2);
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
	
	int input = -1;
	while (true)
	{
		printUserMenu();
		input = inputMenu(4);
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
		case 4:
			showUserByIndex();
			break;
		case 0:
			_currentUser = nullptr;
			return;
		default:
			break;
		}
	}
}

const std::shared_ptr<User> Chat::findUser(std::string &login) const
{
    for (auto &user : _users)
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
    _currentUser = std::make_shared<User>(login, password, name);
    _users.push_back(_currentUser);
}

void Chat::addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string &text)
{
	_messages.push_back(std::make_unique<Message>(to, from, text));
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
			if (findUser(login) == nullptr)
			{
				break; //Если введенный логин валидный и если он свободен, то выходим из цикла ввода логина
			}
			else
			{
				std::cout << "That login is taken.";
				system("pause");
			};
		}
		else
		{
			std::cout << "Incorrect login. Use only [1..0, a..Z] Size: 1-16" << std::endl;
			system("pause");
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
			//std::cout << "Incorrect password. Use only [1..0, a..Z]. Size: 8-128" << std::endl;
			std::cout << "Incorrect password. Use only [1..0, a..Z]. Size: 1-128" << std::endl; ////отключил минимальную длину пароля для удобства. Всё равно пока их не шифруем и не скрываем при вводе.
			system("pause");
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
				system("pause");
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
	system("pause");
}

void Chat::signIn()
{
	std::string login;
	std::cout << "Input login > ";
	getline(std::cin, login);

	_currentUser = findUser(login);
	if (_currentUser == nullptr)
	{
		std::cout << "Login not found." << std::endl << std::endl;
		system("pause");
		return;
	}

	std::string password;
	std::cout << "Input password > ";
	getline(std::cin, password);
	if (_currentUser->getPassword() == password)
	{
		std::cout << std::endl << "Welcome to CChat,  " << _currentUser->getName() << "!" << std::endl << std::endl;
		system("pause");
		menuMain();
	}
	else
	{
		_currentUser = nullptr;
		std::cout << "Wrong password!";
		system("pause");
		return;
	}
}

void Chat::showMessages()
{
	std::string to;
	std::string text;

	if (_messages.empty())
	{
		std::cout << "No messages" << std::endl;
		system("pause");
		return;
	}

	int countPrintMessages{ 0 };
	for (auto &message : _messages)
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

	system("pause");
}

void Chat::printMessage(const std::unique_ptr<Message>& message) const
{
	std::cout << message->getFrom()->getName() << " (" << message->getFrom()->getLogin() << ")" << ": " << message->getText() << std::endl;
}

void Chat::sendPrivateMessage()
{
	std::string login;
	std::cout << "Input login \"To\"> ";
	getline(std::cin, login);

	std::shared_ptr<User> to = findUser(login);
	if (to == nullptr)
	{
		std::cout << "Login not found.";
		return;
	}
	else
	{
		std::string text;
		std::cout << "Input message > ";
		getline(std::cin, text);
		addMessage(to, _currentUser, text);
	}
}

void Chat::sendPublicMessage()
{
	std::string text;
	std::cout << "Input message > ";
	getline(std::cin, text);
	addMessage(nullptr, _currentUser, text);
}

void Chat::printStartMenu()
{
	system("cls");
	std::cout << "CChat:Start menu" << std::endl;
	std::cout << "1 - SignIn" << std::endl;
	std::cout << "2 - SignUp" << std::endl;
	std::cout << "0 - Exit" << std::endl;
	std::cout << std::endl;
}

void Chat::printUserMenu()
{
	system("cls");
	std::cout << "CChat:User menu" << std::endl;
	std::cout << "1 - Show messages" << std::endl;
	std::cout << "2 - Send private message" << std::endl;
	std::cout << "3 - Send public message" << std::endl;
	std::cout << "4 - Show user info by index (only for test exception)" << std::endl;
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
		system("pause");
		return -1;
	}
	else if (input < 0 || input > count)
	{
		std::cout << "Input error: A non-existent menu item is selected." << std::endl << std::endl;
		system("pause");
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
		if (ch >= 48 && ch <= 57 || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
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
	//if (password.length() < 8 || password.length() > 128)
	if (password.length() < 1 || password.length() > 128) //отключил минимальную длину пароля для удобства. Всё равно пока их не шифруем и не скрываем при вводе.
	{
		return false;
	}

	for (char ch : password)
	{
		if (ch < 33 || ch > 122)
		{
			false;
		}
	}
	return true;
}

void Chat::showUserByIndex()
{
	int index = 0;
	std::cout << "Index > ";
	std::cin >> index;
	if (std::cin.fail() || std::cin.get() != '\n' || index < 0) // || index >= _users.size() - удалил проверку ради исключенияю. Нужно класс исключения писать? 
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << "invalid input index" << std::endl << std::endl;
		return;
	}
	
	try
	{
		std::cout << getUserByIndex(index)->getName() << std::endl;
	}
	catch (const char* exception)
	{
		std::cerr << "Exception: " << exception << std::endl;
	}
}

const std::shared_ptr<User> Chat::getUserByIndex(int index) const
{
	if (index < 0 || index >= _users.size())
	{
		throw "index out of range";
	}

	return _users[index];
}

bool Chat::repeat()
{
	int input = -1;
	while (true)
	{
		std::cout << std::endl;
		std::cout << "1 - try again" << std::endl;
		std::cout << "0 - return" << std::endl;
		input = inputMenu(1);
		switch (input)
		{
		case 1:
			return true;
			break;
		case 0:
			return false;
			break;
		default:
			continue;
		}
	}
}
