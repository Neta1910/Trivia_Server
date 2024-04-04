#pragma once
#include <iostream>
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager : public IDatabase
{
public:
	void signUp(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
	
	// IDatabase methods
	bool open() override;
	bool close() ;
	int doesUserExist(std::string username) override;
	int DoesPasswordMatch(std::string username, std::string password) override;
	int addNewUser(std::string username, std::string password, std::string email) override;
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
