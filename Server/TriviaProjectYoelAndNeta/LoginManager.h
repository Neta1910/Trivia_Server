#pragma once
#include <iostream>
#include <iterator>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
#include "SQLiteDatabase.h"

#define ERROR_RETURN_CODE -1

class LoginManager
{
public:
	LoginManager(IDatabase* db);
	bool signUp(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber);
	bool login(std::string username, std::string password);
	bool logout(std::string username);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
