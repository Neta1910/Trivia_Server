#pragma once
#include "Quistion.h"
#include <map>
#include "LoggedUser.h"

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
	Game(GameData& game_data); // C'tor ned to get 'GameData' 
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, unsigned int answer); // Not done implementing
	void removePlayer(LoggedUser user);
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int gameId;
	
	void submitGameStatsToDB(GameData game_data); // Used when the game has ended,    (Not done implementing)
	bool isCurrQuestionLast(LoggedUser user); // Not done implementing
};	
