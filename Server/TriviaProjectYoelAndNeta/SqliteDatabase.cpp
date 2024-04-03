#include "SqliteDatabase.h"
#define CREATE_USERS_TABLE "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, PASSWORD TEXT, EMAIL TEXT);"
#define NAME "NAME"
#define PASSWORD "PASSWORD"
#define EMAIL "EMAIL"
#define ID "ID"
std::vector<User> SQLiteDatabase::users;

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

bool SQLiteDatabase::doesUserExist(const std::string& userName)
{
	std::string query = "SELECT COUNT(*) FROM Users WHERE NAME = \"" + userName + "\";";
	int times = 0;
	this->runCommand(query, countCallback, &times);

	return times > 0;
}
bool SQLiteDatabase::doesPasswordMatch(const std::string& password1, const std::string& password2)
{
	return password1 == password2;
}

void SQLiteDatabase::addNewUser(const std::string& name, const std::string& password, const std::string& email)
{
	std::string query = "INSERT INTO Users (NAME, PASSWORD, EMAIL) VALUES(\"" + name + "\", \"" + password + "\", \"" + email + "\");";
	this->runCommand(query);
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

int loadIntoUsers(void* data, int argc, char** argv, char** azColName)
{
	User user(0, "", "", "");

	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == NAME) {
			user.setName(argv[i]);
		}
		else if (std::string(azColName[i]) == ID) {
			user.setId(std::stoi(argv[i]));
		}
		else if (std::string(azColName[i]) == EMAIL) {
			user.setEmail(argv[i]);
		}
		else if (std::string(azColName[i]) == PASSWORD) {
			user.setPassword(argv[i]);
		}
	}
	SQLiteDatabase::users.push_back(user);
	return 0;
}

/**
 * countCallback - Callback function to count results.
 * Params: data - Data pointer, argc - Number of columns, argv - Array of column values,
 *         azColName - Array of column names
 * Returns: 0 to indicate success.
 */
int countCallback(void* data, int argc, char** argv, char** azColName)
{
	int* count = static_cast<int*>(data);
	if (argv[0]) {
		*count = std::stoi(argv[0]);
	}
	return 0;
}
