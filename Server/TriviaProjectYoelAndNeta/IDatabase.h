#pragma once
#include <iostream>

class IDatabase
{
public: 
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(std::string username) = 0;
	virtual int DoesPasswordMatch(std::string username, std::string password) = 0;
	virtual int addNewUser(std::string username, std::string password, std::string email) = 0;
};