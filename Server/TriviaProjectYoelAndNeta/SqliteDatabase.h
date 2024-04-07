#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#define DB "Trivia.db"
#include "User.h"
#include <vector>
#include <iostream>


#define CREATE_USERS_TABLE "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, PASSWORD TEXT, EMAIL TEXT);"
#define NAME "NAME"
#define PASSWORD "PASSWORD"
#define EMAIL "EMAIL"
#define ID "ID"


int loadIntoUsers(void* data, int argc, char** argv, char** azColName);
int countCallback(void* data, int argc, char** argv, char** azColName);
int callbackUserPassword(void* _data, int argc, char** argv, char** azColName);

class SQLiteDatabase : public IDatabase
{
public:
	SQLiteDatabase();
	static std::vector<User> users;
	virtual bool open() override;
	virtual bool close() override;
	virtual bool doesUserExist(const std::string& username) override;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	virtual bool addNewUser(const std::string& name, const std::string& password, const std::string& email) override;

private:
	sqlite3* _db;
	bool runCommand(const std::string& sqlStatement, int(*callback)(void*, int, char**, char**) = nullptr, void* secondParam = nullptr);
};
