#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#define DB "Trivia.db"

class SQLiteDatabase : public IDatabase
{
public:
	SQLiteDatabase();
	virtual bool open() override;
	virtual bool close() override;
	virtual bool doesUserExist(const std::string& userName);
	virtual bool doesPasswordMatch(const std::string& password1, const std::string& password2);
	virtual void addNewUser(const std::string& name, const std::string& password, const std::string& email);

private:
	sqlite3* _db;
	bool runCommand(const std::string& sqlStatement, int(*callback)(void*, int, char**, char**) = nullptr, void* secondParam = nullptr);
};