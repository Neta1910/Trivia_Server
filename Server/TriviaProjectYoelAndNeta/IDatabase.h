#pragma once
#include "pch.h"

class IDatabase
{
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(const std::string& userName) = 0;
	virtual bool doesPasswordMatch(const std::string& password1, const std::string& password2) = 0;
	virtual void addNewUser(const std::string& name, const std::string& password, const std::string& email) = 0;
};
