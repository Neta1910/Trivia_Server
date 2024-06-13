#include "Room.h"
#include "pch.h"
Room::Room(RoomData metadata, std::vector<LoggedUser*> users) :
	m_metadata(metadata), m_users(users)
{
}

Room::Room()
{
	m_metadata = { 0, "One on One", PLAYERS_IN_ONE_ON_ONE, QUESTIONS_IN_ONE_ON_ONE, TIMEOUT_IN_ONE_ON_ONE, true, false, 0, 0 };
}

void Room::addUser(LoggedUser* logged_user)
{	
	m_users.push_back(logged_user);
}

void Room::removeUser(LoggedUser* logged_user)
{
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		if ((*it)->getUsername() == logged_user->getUsername()) // Find username with name to delete
		{
			m_users.erase(it);
		}
	}
}

// Create vector of all the connected users' usernames
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> all_users; // Result vector
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		all_users.push_back((*it)->getUsername());
	}
	return all_users;
}

RoomData& Room::getRoomData()
{
	return m_metadata;
}

std::vector<LoggedUser*> Room::getAllLoggedUsers()
{
	return m_users;
}
