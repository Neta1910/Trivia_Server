#pragma once
#include <iostream>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager
{
public:
	LoginManager(IDatabase* db);
	bool signUp(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	bool logout(std::string username);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
