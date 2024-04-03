#pragma once
#include "pch.h"

class User
{
public:
	User(const std::string& name, const std::string& password, const std::string& email );

private:
	std::string _userName;
	std::string _password;
	std::string _email;
};