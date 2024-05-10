#pragma once
#include "Quistion.h"
#include <map>
#include "LoggedUser.h"

class Question; 

typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};

class Game
{
public:
	//Game(GameData& game_data); // C'tor ned to get 'GameData' 
	Game(const std::vector<Question> questions, const std::vector<LoggedUser> players, const  unsigned int gameId);
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, unsigned int answer); // Not done implementing
	void removePlayer(LoggedUser user);
	bool areAllPlayersDonePlaying();
	std::map<LoggedUser, GameData> getAllPlayers();	
	int getGameId();
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int m_gameId;
	
	void submitGameStatsToDB(GameData game_data); // Used when the game has ended,    (Not done implementing)
	bool isCurrQuestionLast(LoggedUser user); // Not done implementing
};	
