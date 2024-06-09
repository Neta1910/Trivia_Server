#pragma once
#include <iostream>
#include "Quistion.h"
#include "HighestScore.h"
#include "Game.h"
#include "GameData.h"
#include <list>
#include "PlayerResults.h"

class Game;

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	virtual bool addNewUser(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& bitrthDate, const std::string& phoneNumber) = 0;
	virtual int getUserId(const std::string& name, const std::string& password) = 0;
	
	// ---- Questions related ----
	virtual std::list<Question> getQuestions(const int& amount) = 0;
	virtual void loadQuestionsIntoDB(int amount) = 0;
	virtual void insertQuestionIntoDB(Question question) = 0;
	virtual int getTotalAmountOfQuestions() = 0;

	// ---- Statistics related ----
	virtual PlayerResults getPlayersStat(int user_id) = 0;
	virtual std::vector<PlayerResults> getHighScores() = 0; // Return 5 highest scores
	virtual int submitGameStatistics(GameData game_data, LoggedUser user) = 0;
	virtual bool doesUserHaveStats(const int& id) = 0;
};
