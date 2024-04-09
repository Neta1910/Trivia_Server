#include "SqliteDatabase.h"

std::vector<User> SQLiteDatabase::users;
std::list<Question>  SQLiteDatabase::questions;

SQLiteDatabase::SQLiteDatabase() :
	IDatabase()
{
	this->open();
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
	this->runCommand(CREATE_QUISTIONS_TABLE);
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
bool SQLiteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	std::string userPassword; 
	std::string query = "SELECT PASSWORD FROM USERS WHERE USERNAME = '" + username + "';";
	runCommand(query, callbackUserPassword, &userPassword);
	return userPassword == password;
}

bool SQLiteDatabase::addNewUser(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber)
{
	std::string query = "INSERT INTO Users (NAME, PASSWORD, EMAIL, ADDRESS, PHONE_NUMBER, BIRTH_DATE) VALUES(\"" + name + "\", \"" + password + "\", \"" + email + "\", \"" + address + "\", \"" +  phoneNumber + "\", \"" + bitrthDate + "\");";
	this->runCommand(query);
	return true;
}

std::list<Question> SQLiteDatabase::getQuestions(const int& amount)
{
	std::string query = "SELECT * FROM t_questions LIMIT " + std::to_string(amount) + " ;";
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
	return true;
}

int loadIntoUsers(void* data, int argc, char** argv, char** azColName)
{
	User user(0, "", "", "", "", "", "");

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

int callbackUserPassword(void* _data, int argc, char** argv, char** azColName)
{
	auto& password = *static_cast<std::string*>(_data);

	if (std::string(azColName[0]) == PASSWORD)
		password = argv[0];

	return 0;
}