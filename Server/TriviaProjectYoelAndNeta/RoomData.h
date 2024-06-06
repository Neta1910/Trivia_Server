#pragma once
#include <iostream>
#include <string>
struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
	bool isGameBegun;
	unsigned int roomAdmin;
	unsigned int game_id;
} typedef RoomData;
