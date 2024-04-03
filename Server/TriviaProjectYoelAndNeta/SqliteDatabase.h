#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#define DB "Trivia.db"
#include "User.h"

int loadIntoUsers(void* data, int argc, char** argv, char** azColName);
int countCallback(void* data, int argc, char** argv, char** azColName);

class SQLiteDatabase : public IDatabase
{
public:
	SQLiteDatabase();
	static std::vector<User> users;
	virtual bool open() override;
	virtual bool close() override;
	virtual bool doesUserExist(const std::string& userName);
	virtual bool doesPasswordMatch(const std::string& password1, const std::string& password2);
	virtual void addNewUser(const std::string& name, const std::string& password, const std::string& email);

private:
	sqlite3* _db;
	bool runCommand(const std::string& sqlStatement, int(*callback)(void*, int, char**, char**) = nullptr, void* secondParam = nullptr);
};