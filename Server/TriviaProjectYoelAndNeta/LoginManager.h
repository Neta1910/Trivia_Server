#pragma once
#include <iostream>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager
{
public:
	LoginManager(IDatabase* m_database);
	void signUp(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
