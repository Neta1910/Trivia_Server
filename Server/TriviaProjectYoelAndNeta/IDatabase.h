#pragma once
#include <iostream>
#include "Quistion.h"
#include <list>
class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	virtual bool addNewUser(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber) = 0;

	// quistions related
	virtual std::list<Question> getQuestions(const int& amount) = 0;
	virtual void refreshQuestionsInDB() = 0;

};
