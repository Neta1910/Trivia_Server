#include "GameManager.h"

GameManager::GameManager(IDatabase* db) : m_database(db)
{
}

Game* GameManager::createGame(Room* room)
{
	std::vector<LoggedUser*> players = room->getAllLoggedUsers();
	std::list<Question> questions = m_database->getQuestions(room->getRoomData().numOfQuestionsInGame);
	std::vector<Question> questions_formatted{ std::begin(questions), std::end(questions) };

	Game* new_game = new Game(questions_formatted, players, room->getRoomData().id);	

	m_games.push_back(new_game);
	return new_game;
}

void GameManager::deleteGame(int game_id)
{
	delete getGameForId(game_id);
}

Game* GameManager::getGame(int game_id)
{
	for (auto it : m_games)
	{
		if ((*it).getGameId() == game_id)
		{
			return it;
		}
	}
}

Game* GameManager::getGameForId(int game_id)
{
	for (auto& game : m_games)
	{
		if ((*game).getGameId() == game_id)
		{
			return game;
		}
	}
}
