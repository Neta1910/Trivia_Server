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
	m_users_mutex.lock();
	// Check if player already in the room
	if (std::find(m_users.begin(), m_users.end(), logged_user) != m_users.end())
	{
		m_users_mutex.unlock();
		throw std::exception(USER_ALREADY_IN_ROOM + m_metadata.id);
	}
	// Check if number of players limit reached
	else if (m_users.size() == m_metadata.maxPlayers)
	{
		m_users_mutex.unlock();
		throw std::exception(ROOM_FULL + m_metadata.id);
	}
	else
	{
		m_users.push_back(logged_user);
		m_users_mutex.unlock();
	}
}

void Room::removeUser(LoggedUser* logged_user)
{
	m_users_mutex.lock();
	// Check if player is in the room
	if (std::find(m_users.begin(), m_users.end(), logged_user) == m_users.end())
	{
		m_users_mutex.unlock();
		throw std::exception(USER_NOT_PART_OF_ROOM + logged_user->getId());
	}
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		if ((*it)->getUsername() == logged_user->getUsername()) // Find username with name to delete
		{
			m_users.erase(it);
		}
	}
	m_users_mutex.unlock();
}

// Create vector of all the connected users' usernames
std::vector<std::string> Room::getAllUsers()
{
	m_users_mutex.lock();

	std::vector<std::string> all_users; // Result vector
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		all_users.push_back((*it)->getUsername());
	}

	m_users_mutex.unlock();
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
