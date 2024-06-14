#include "RoomManager.h"

int RoomManager::createRoom(LoggedUser* logged_user, RoomData room_data)
{
	// Create new room

	// Add room to map of rooms
	int roomId = 0;

	// creating loop to decide what is a unique id to use for a room
	for (auto it : m_rooms) {
		if (it.second->getRoomData().id > roomId)
		{
			roomId = it.second->getRoomData().id;
		}
	}

	roomId++;
	room_data.id = roomId;

	Room* new_room = new Room(room_data, std::vector<LoggedUser*>());
	new_room->addUser(logged_user);
	this->m_rooms.insert({ roomId, new_room });
	
	return roomId;
}

void RoomManager::deleteRoom(int room_id)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
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
	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if ((*it).second->getRoomData().id == room_id)
		{
			return (*it).second->getRoomData().isActive;
		}
	}
}

bool RoomManager::doesRoomExist(int room_id)
{

	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
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
	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{	
		if ((!(*it).second->getRoomData().isGameBegun) && (*it).second->getRoomData().isActive)
		{
			rooms_data.push_back((*it).second->getRoomData());
		}
	}
	return rooms_data;
}

Room* RoomManager::getRoom(int room_id)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if ((*it).first == room_id)
		{			
			return (*it).second;
		}
	}	
}

OneOnOne* RoomManager::getCurr()
{
	return currRoom;
}

void RoomManager::createNewCurr()
{
	currRoom = new OneOnOne(0);
}
