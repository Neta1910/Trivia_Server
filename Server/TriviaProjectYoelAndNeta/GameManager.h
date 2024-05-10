#pragma once
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"
#include <vector>

class RequestHandlerFactory;

class GameManager
{
public:
	GameManager(IDatabase* db);
	Game& createGame(Room& room);
	void deleteGame(int game_id);
private:
	IDatabase* m_database;
	std::vector<Game*> m_games;

	Game* getGameForId(int game_id);
};
