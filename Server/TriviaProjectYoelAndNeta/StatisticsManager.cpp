#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db)
{
	m_database = db;
}

std::vector<PlayerResults> StatisticsManager::getHighScore()
{
	return m_database->getHighScores();
}

PlayerResults StatisticsManager::getUserStatistics(int user_id)
{
	PlayerResults res = this->m_database->getPlayersStat(user_id);
	return res;
}
