#pragma once

#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>
#include <iterator>
#include <mutex>

class Room
{
public:
	Room(RoomData metadata, std::vector<LoggedUser*> users);
	Room();
	virtual void addUser(LoggedUser* logged_user);
	void removeUser(LoggedUser* logged_user);
	std::vector<std::string> getAllUsers();
	RoomData& getRoomData();
	std::vector<LoggedUser*> getAllLoggedUsers();
protected:
	RoomData m_metadata;
	std::vector<LoggedUser*> m_users;
	mutable std::mutex m_users_mutex;
};
