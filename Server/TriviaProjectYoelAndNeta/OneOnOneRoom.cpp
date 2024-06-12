#include "OneOnOneRoom.h"
#include "pch.h"
OneOnOne::OneOnOne(int room_id) : Room()

{
}

bool OneOnOne::isRoomFull() const
{
	return  m_users.size() > PLAYERS_IN_ONE_ON_ONE;
}

void OneOnOne::addUser(LoggedUser* logged_user)
{
	if (!isRoomFull())
	{
		m_users.push_back(logged_user);
	}
}
