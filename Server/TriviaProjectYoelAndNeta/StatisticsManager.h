#pragma once
#include <vector>
#include <iostream>
#include "IDatabase.h"
#define NUM_OF_SCORES 3

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* db);
	std::vector<PlayerResults> getHighScore();
	PlayerResults getUserStatistics(int user_id);
private:
	IDatabase* m_database;
};
