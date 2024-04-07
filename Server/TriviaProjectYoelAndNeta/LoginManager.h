#pragma once
#include <iostream>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager : public IDatabase
{
public:
	LoginManager(IDatabase* m_database);
	void signUp(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
	
	// IDatabase methods
	virtual bool open() override;
	virtual bool close() override;
	virtual bool doesUserExist(const std::string& username) override;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	virtual bool addNewUser(const std::string& name, const std::string& password, const std::string& email) override;
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
