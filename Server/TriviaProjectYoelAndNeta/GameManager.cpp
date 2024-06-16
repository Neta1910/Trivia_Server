#include "GameManager.h"

GameManager::GameManager(IDatabase* db) : m_database(db)
{
}

Game* GameManager::createGame(Room* room)
{
	std::vector<LoggedUser*> players = room->getAllLoggedUsers();
	std::list<Question> questions = m_database->getQuestions(room->getRoomData().numOfQuestionsInGame);
	std::vector<Question> questions_formatted{ std::begin(questions), std::end(questions) };

	Game* new_game = new Game(questions_formatted, players, room->getRoomData().id, m_database);

	m_games_mutex.lock();
	m_games.push_back(new_game);
	m_games_mutex.unlock();

	return new_game;
}

void GameManager::deleteGame(int game_id)
{
	m_games_mutex.lock();
	delete getGameForId(game_id);
	m_games_mutex.unlock();
}

Game* GameManager::getGame(int game_id)
{
	m_games_mutex.lock();
	for (auto it : m_games)
	{
		if ((*it).getGameId() == game_id)
		{
			m_games_mutex.unlock();
			return it;
		}
	}
	m_games_mutex.unlock();
}

Game* GameManager::getGameForId(int game_id)
{
	m_games_mutex.lock();
	for (auto& game : m_games)
	{
		if ((*game).getGameId() == game_id)
		{
			m_games_mutex.unlock();
			return game;
		}
	}
}
