#include "SqliteDatabase.h"

#define CREATE_USERS_TABLE "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, PASSWORD TEXT, EMAIL TEXT);"
SQLiteDatabase::SQLiteDatabase() :
	IDatabase()
{
}

bool SQLiteDatabase::open()
{
	sqlite3* db;
	int rc = sqlite3_open(DB, &db);
	if (rc) {
		return false;
	}
	this->_db = db;
	this->runCommand(CREATE_USERS_TABLE);
	return true;
}

bool SQLiteDatabase::close()
{
	return true;
}

bool SQLiteDatabase::runCommand(const std::string& sqlStatement, int(*callback)(void*, int, char**, char**), void* secondParam)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callback, secondParam, errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "error code: " << res;
		return false;
	}
}
