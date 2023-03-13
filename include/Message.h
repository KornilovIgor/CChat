#pragma once

#include "User.h"

#include <string>
#include <memory>

class Message
{
	const std::shared_ptr<User> _to;
	const std::shared_ptr<User> _from;
	const std::string _text;

public:
	Message(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string text):
	_to(to), _from(from), _text(text)
	{};

	const std::shared_ptr<User> getTo() const;
	const std::shared_ptr<User> getFrom() const;
	const std::string & getText() const;
};