#include "RoomManager.h"

int RoomManager::createRoom(LoggedUser logged_user, RoomData room_data)
{
	// Create new room
	Room new_room = Room(room_data);
	new_room.addUser(logged_user);

	// Add room to map of rooms
	int roomId = 0;

	// creating loop to decide what is a unique id to use for a room
	for (auto it : m_rooms) {
		if (it.second.getRoomData().id > roomId)
		{
			roomId = it.second.getRoomData().id;
		}
	}
	roomId++;
	this->m_rooms.insert({ roomId, new_room });
	return roomId;
}

void RoomManager::DeleteRoom(int room_id)
{
	std::map<int, Room>::iterator it;
	for (it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if ((*it).first == room_id) // Find matching room id
		{
			m_rooms.erase(it);
			return;
		}
	}
}

unsigned int RoomManager::getRoomState(int room_id)
{
	std::map<int, Room>::iterator it;
	for (it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if ((*it).second.getRoomData().id == room_id)
		{
			return (*it).second.getRoomData().isActive;
		}
	}
}

bool RoomManager::doesRoomExist(int room_id)
{
	std::map<int, Room>::iterator it;
	for (it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if ((*it).first == room_id)
		{
			return true;
		}
	}
	return false;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms_data;
	std::map<int, Room>::iterator it;
	for (it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{		
		rooms_data.push_back((*it).second.getRoomData());
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
