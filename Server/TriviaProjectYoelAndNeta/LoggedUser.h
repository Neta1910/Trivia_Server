#pragma once
#include <iostream>

class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername() const ;
	bool operator==(const LoggedUser& other);
private:
	std::string m_username;
};
