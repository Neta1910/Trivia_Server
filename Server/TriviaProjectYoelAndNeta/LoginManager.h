#pragma once
#include <iostream>
#include <iterator>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
#include "SQLiteDatabase.h"

#define ERROR_RETURN_CODE -1

class RequestHandlerFactory;

class LoginManager
{
public:
	
	static LoginManager& getInstance(IDatabase* db)
	{
		static LoginManager instance(db);
		return instance;	
	}

	// Delete copy constructor and assignment operator for singleton
	LoginManager(LoginManager const&) = delete;
	void operator=(LoginManager const&) = delete;

	LoginManager(IDatabase* db);
	LoggedUser* signUp(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber);
	LoggedUser* login(std::string username, std::string password);
	bool logout(std::string username);

	std::vector<LoggedUser*> getUsers() const;
private:
	IDatabase* m_database;
	std::vector<LoggedUser*> m_loggedUsers;
};
