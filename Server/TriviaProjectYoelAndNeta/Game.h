#pragma once
#include "Quistion.h"
#include <map>
#include "LoggedUser.h"
#include "pch.h"
#include "IDatabase.h"
#include "GameData.h"

class Question; 
class IDatabase;

class Game
{
public:
	//Game(GameData& game_data); // C'tor ned to get 'GameData' 
	Game(const std::vector<Question> questions, const std::vector<LoggedUser*> players, const  unsigned int gameId);
	Question getQuestionForUser(LoggedUser* user);
	int submitAnswer(LoggedUser* user, unsigned int answer); 
	void removePlayer(LoggedUser* user);
	bool areAllPlayersDonePlaying();
	std::map<LoggedUser*, GameData> getAllPlayers();	
	int getGameId();
private:
	std::vector<Question> m_questions;
	mutable std::map<LoggedUser*, int> m_question_of_user;
	mutable std::map<LoggedUser*, GameData> m_players;
	unsigned int m_gameId;
	IDatabase* m_database;

	void submitGameStatsToDB(GameData game_data); // Used when the game has ended,    (Not done implementing)
	bool isCurrQuestionLast(LoggedUser user); // Not done implementing
};	
