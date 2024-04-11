#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#define DB "Trivia.db"
#include "User.h"
#include <vector>
#include <iostream>
#include <list>
#include <Windows.h>
#include <WinInet.h>

#pragma comment(lib, "wininet.lib")

#define CREATE_USERS_TABLE "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, PASSWORD TEXT, EMAIL TEXT, ADDRESS TEXT, PHONNE_NUMBER TEXT, BIRTH_DATE TEXT);"
#define CREATE_QUISTIONS_TABLE "CREATE TABLE IF NOT EXISTS t_questions (question_id	integer NOT NULL, question	text NOT NULL, correct_ans	text NOT NULL, ans2	text NOT NULL,  ans3	text NOT NULL, ans4	text NOT NULL, PRIMARY KEY(question_id AUTOINCREMENT) );"
#define CREATE_STATISTICS_TABLE "CREATE TABLE IF NOT EXISTS Statistics (ID INTEGER, AVERAGE_ANS_TIME INTEGER, CORRECT_ANS INTEGER, TOTAL_ANS INTEGER, PALYERS_GAME INTEGER, FOREIGN KEY(ID) REFERENCES Users(ID));"



#define NAME "NAME"
#define PASSWORD "PASSWORD"
#define EMAIL "EMAIL"
#define ID "ID"

// t_questions
#define QUESTION_ID "question_id"
#define QUESTION "question"
#define CORRECT_ANS "correct_ans"
#define ANS_2 "ans2"
#define ANS_3 "ans3"
#define ANS_4 "ans4"



int loadIntoUsers(void* data, int argc, char** argv, char** azColName);
int countCallback(void* data, int argc, char** argv, char** azColName);
int callbackUserPassword(void* _data, int argc, char** argv, char** azColName);
int loadIntoQuestions(void* _data, int argc, char** argv, char** azColName);

class SQLiteDatabase : public IDatabase
{
public:
	static SQLiteDatabase& getInstance()
	{
		static SQLiteDatabase instance;
		return instance;
	}

	static std::list<Question> questions;

	// Delete copy constructor and assignment operator for singleton
	SQLiteDatabase(SQLiteDatabase const&) = delete;
	void operator=(SQLiteDatabase const&) = delete;


	SQLiteDatabase();
	static std::vector<User> users;
	virtual bool open() override;
	virtual bool close() override;

	// user related
	virtual bool doesUserExist(const std::string& username) override;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	virtual bool addNewUser(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber) override;

	// quistions related
	virtual std::list<Question> getQuestions(const int& amount) override;
	virtual void loadQuestionsIntoDB() override;
	virtual void insertQuestionIntoDB(Question question);

private:
	sqlite3* _db;
	bool runCommand(const std::string& sqlStatement, int(*callback)(void*, int, char**, char**) = nullptr, void* secondParam = nullptr);
};
