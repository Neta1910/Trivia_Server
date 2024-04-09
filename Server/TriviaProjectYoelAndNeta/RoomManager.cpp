#include "RoomManager.h"

std::vector<Room> RoomManager::getRooms()
{
	std::vector<Room> rooms_data;
	std::map<int, Room>::iterator it;
	for (it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{		
		rooms_data.push_back((*it).second);
	}
	return rooms_data;
}

Room& RoomManager::getRoom(int room_id)
{
	std::map<int, Room>::iterator it;
	for (it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if ((*it).first == room_id)
		{			
			return (*it).second;
		}
	}
}
