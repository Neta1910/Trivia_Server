#include "SqliteDatabase.h"
#include "json.hpp"
#include "RequestStructs.h"

using json = nlohmann::json;


std::vector<User> SQLiteDatabase::users;
std::list<Question>  SQLiteDatabase::questions;
std::vector<PlayerResults> SQLiteDatabase::usersStats;

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
	// Create Tables
	this->runCommand(CREATE_USERS_TABLE);
	this->runCommand(CREATE_QUESTIONS_TABLE);
	this->runCommand(CREATE_STATISTICS_TABLE);
	this->runCommand(CREATE_HIGHEST_SCORES_TABLE);
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
	std::string query = "SELECT PASSWORD FROM USERS WHERE NAME = '" + username + "';";
	runCommand(query, callbackUserPassword, &userPassword);
	return userPassword == password;
}

bool SQLiteDatabase::addNewUser(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber)
{
	std::string query = "INSERT INTO Users (NAME, PASSWORD, EMAIL, ADDRESS, PHONE_NUMBER, BIRTH_DATE) VALUES(\"" + name + "\", \"" + password + "\", \"" + email + "\", \"" + address + "\", \"" +  phoneNumber + "\", \"" + bitrthDate + "\");";
	this->runCommand(query);
	return true;
}

int SQLiteDatabase::getUserId(const std::string& name, const std::string& password)
{
	std::string query = "SELECT ID FROM Users WHERE name == \"" + name + "\" and PASSWORD == \"" + password + "\"";
	int id = 0;
	this->runCommand(query, integerCallBack, &id);
	return id;
}

std::list<Question> SQLiteDatabase::getQuestions(const int& amount)
{
	// getting count of questions, and if its too low - updating questions
	int amountOfQuestions = 0;
	this->runCommand("SELECT COUNT(*) FROM t_questions", countCallback, &amountOfQuestions);
	if (amountOfQuestions < amount)
	{
		this->loadQuestionsIntoDB(amount - amountOfQuestions + 1);
	}
	std::string query = "SELECT * FROM t_questions LIMIT " + std::to_string(amount) + " ;";
	this->runCommand(query, loadIntoQuestions);
	return SQLiteDatabase::questions;
}

void SQLiteDatabase::loadQuestionsIntoDB(int amount)
{
	HINTERNET hInternet = InternetOpenA("HTTPGET", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternet) {
		std::cerr << "Failed to open internet handle" << std::endl;
		return;
	}
	std::string url = "https://opentdb.com/api.php?amount=" + std::to_string(amount) + "& category = 9 & difficulty = hard & type = multiple";
	HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (!hConnect) {
		std::cerr << "Failed to open URL" << std::endl;
		InternetCloseHandle(hInternet);
		return;
	}

	char buf[1024];
	DWORD bytesRead;
	std::string response;

	while (InternetReadFile(hConnect, buf, sizeof(buf), &bytesRead) && bytesRead > 0) {
		response.append(buf, bytesRead);
	}

	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	// turning string into json
	json jsonObject = json::parse(response);
	jsonObject = jsonObject["results"];
	for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it)
	{
		std::vector<std::string> incorrectAnswers;
		for (auto it : it.value()["incorrect_answers"])
		{
			incorrectAnswers.push_back(it);
		}
		Question question(it.value()["question"], incorrectAnswers, it.value()["correct_answer"]);
		this->insertQuestionIntoDB(question);
	}
}

void SQLiteDatabase::insertQuestionIntoDB(Question question)
{
	int i = 0;
	std::string sql;
	switch (question.getPossibleAnswers().size())
	{
	case 1:
		sql = "INSERT INTO t_questions (question, correct_ans, ans2) VALUES (\"";
		break;
	case 2:
		sql = "INSERT INTO t_questions (question, correct_ans, ans2, ans3) VALUES (\"";
		break;
	case 3:
		sql = "INSERT INTO t_questions (question, correct_ans, ans2, ans3, ans4) VALUES (\"";
		break;
	default:
		break;
	}

	sql += question.getQuestion();
	sql += "\", \"";
	sql += question.getCorrectAnswer();
	sql += "\", \"";
	if (question.getPossibleAnswers().size() == 1)
	{
		sql += question.getPossibleAnswers()[0];
	}
	else
	{
		for (i = 0; i < question.getPossibleAnswers().size() - 1; i++)
		{
			sql += question.getPossibleAnswers()[i];
			sql += "\", \"";
		}
		if (question.getPossibleAnswers().size() > i)
			sql += question.getPossibleAnswers()[i];
	}

	sql += "\");";

	this->runCommand(sql);
}

int SQLiteDatabase::getTotalAmountOfQuestions()
{
	//std::string query = "SELECT * FROM t_questions;";
	//this->runCommand(query, loadIntoQuestions);
	//return SQLiteDatabase::questions.size();
	// returining one for now

	return 100;
}

PlayerResults SQLiteDatabase::getPlayersStat(int user_id)
{
	this->runCommand("SELECT * from Statistics where id = " + std::to_string(user_id), loadIntoUsersStats);
	return SQLiteDatabase::usersStats[0];
}

std::vector<PlayerResults> SQLiteDatabase::getHighScores()
{
	std::vector<HighestScore> highestScores;
	std::string query = "SELECT * FROM Statistics";
	this->runCommand(query, loadIntoUsersStats);
	std::sort(SQLiteDatabase::usersStats.begin(), SQLiteDatabase::usersStats.end(), [](auto& a, auto& b) {
		return a < b;
		});
	return SQLiteDatabase::usersStats;
}

int SQLiteDatabase::submitGameStatistics(GameData game_data, LoggedUser user)
{
	// Update statistics table
	
	// checking if user exsists

	if (!this->doesUserHaveStats(user.getId()))
	{
		this->runCommand("INSERT INTO Statistics (ID, AVERAGE_ANS_TIME, correct_ans, TOTAL_ANS, GAMES_PLAYED, USER_NAME) VALUES(" + std::to_string(user.getId()) + ", " + std::to_string(game_data.averageAnswerTime) + ", " + std::to_string(game_data.correctAnswerCount) + ", " + std::to_string(game_data.wrongAnswerCount + game_data.correctAnswerCount) + ", 0 , \"" + user.getUsername() + "\")");
	}
	else
	{
		PlayerResults currStats = this->getPlayersStat(user.getId());
		std::string correctAnsCount_query = "UPDATE Statistics SET CORRECT_ANS = CORRECT_ANS + " + std::to_string(game_data.correctAnswerCount) + " WHERE ID = " + std::to_string(user.getId()) + ";";
		runCommand(correctAnsCount_query);
		std::string wrongAnsCount_query = "UPDATE Statistics SET WRONG_ANS = WRONG_ANS + " +  std::to_string(game_data.wrongAnswerCount) + " WHERE ID = " + std::to_string(user.getId()) + ";";
		runCommand(wrongAnsCount_query);
		std::string avgAnsTime_query = "UPDATE Statistics SET AVERAGE_ANS_TIME = " + std::to_string((currStats.averageAnswerTime + game_data.averageAnswerTime) / (currStats ) + " WHERE ID = " + std::to_string(user.getId()) + ";";
		runCommand(avgAnsTime_query);
	}
	return 0;
}

bool SQLiteDatabase::doesUserHaveStats(const int& id)
{
	int occurrences = 0;
	this->runCommand("SELECT COUNT (*) FROM Statistics WHERE ID == " + std::to_string(id), countCallback, &occurrences);
	return occurrences != 0;
}



bool SQLiteDatabase::runCommand(const std::string& sqlStatement, int(*callback)(void*, int, char**, char**), void* secondParam)
{
	SQLiteDatabase::users.clear();
	SQLiteDatabase::questions.clear();
	SQLiteDatabase::usersStats.clear();
	char** errMessage = nullptr;
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callback, secondParam, errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "error code: " << res;
		return false;
	}
	return true;
}

bool SQLiteDatabase::comparePasswords(const std::string& onePassword, const std::string& secondPassword)
{
	if (onePassword.length() != secondPassword.length())
	{
		return false;
	}
	for (int i = 0; i < onePassword.length(); i++)
	{
		if (onePassword[i] != secondPassword[i])
		{
			return false;
		}
	}
	return true;
}

float SQLiteDatabase::getAverageAnsTime(unsigned int user_id)
{
	float averageAnsTime;
	std::string query = "SELECT AVERAGE_ANS_TIME FROM Statistics WHERE ID = " + std::to_string(user_id) + " ;";
	this->runCommand(query, floatCallBack, &averageAnsTime);
	return averageAnsTime;
}

float SQLiteDatabase::calcNewAverageAnsTime(unsigned int user_id, float new_average_time)
{
	return (getAverageAnsTime(user_id) + new_average_time) / getNumOfPlayerGames(user_id);
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

int loadIntoQuestions(void* _data, int argc, char** argv, char** azColName)
{
	Question question = Question();
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == QUESTION) {
			question.setQuestion(argv[i]);
		}
		else if (std::string(azColName[i]) == QUESTION_ID) {
			question.setId(std::stoi(argv[i]));
		}
		else if (std::string(azColName[i]) == CORRECT_ANS) {
			question.setCorrectAnswer(argv[i]);
		}
		else if (std::string(azColName[i]) == ANS_2 || std::string(azColName[i]) == ANS_3 || std::string(azColName[i]) == ANS_4) {
			if (argv[i] != NULL) {
				question.insertOptional(argv[i]);
			}
		}
	}
	SQLiteDatabase::questions.push_back(question);
	return 0;
}

int floatCallBack(void* _data, int argc, char** argv, char** azColName)
{
	auto averageAnsTime = *static_cast<float*>(_data);
	if (argc == 1 && argv[0] != nullptr)
	{
		averageAnsTime == std::stoi(argv[0]);
		return 0;
	}
	else
	{
		throw std::invalid_argument("The user dosent have stats");
	}
	return 1;
}

int integerCallBack(void* _data, int argc, char** argv, char** azColName)
{
	auto& averageAnsTime = *static_cast<int*>(_data);
	if (argc == 1 && argv[0] != nullptr)
	{
		averageAnsTime = std::atoi(argv[0]);
		return 0;
	}
	return 1;
}

int loadIntoUsersStats(void* _data, int argc, char** argv, char** azColName)
{
	PlayerResults playerResult;
	int total = 0;
	int correct_sum = 0;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == AVG_TIME)
		{
			playerResult.averageAnswerTime = std::stoi(argv[i]);
		}
		else if (std::string(azColName[i]) == CORRECT_ANSWER_COUNT)
		{
			correct_sum = std::stoi(argv[i]);
			playerResult.correctAnswerCount = correct_sum;
		}
		else if (std::string(azColName[i]) == TOTAL_ANS_COUNT)
		{
			total = std::stoi(argv[i]);
		}
		else if (std::string(azColName[i]) == USER_NAME_USER_STATS)
		{
			playerResult.username = argv[i];
		}
	}
	playerResult.wrongAnswerCount = total - correct_sum;
	SQLiteDatabase::usersStats.push_back(playerResult);
	return 0;
}

