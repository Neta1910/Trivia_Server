#pragma once
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"
#include <vector>

class GameManager
{
public:
	GameManager(){}
	Game createGame(Room room);
	void deleteGame(int game_id);
private:
	IDatabase* m_database;
	std::vector<Game> m_games;
};
