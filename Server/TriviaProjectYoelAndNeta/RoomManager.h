#pragma once
#include <map>
#include "Room.h"
#include "OneOnOneRoom.h"
class RoomManager
{
public:
	RoomManager() { 
		currRoom = new OneOnOne(0);
		m_oneOnOne_rooms.insert({ 0, currRoom });
	};

	int createRoom(LoggedUser* logged_user, RoomData room_data);
	void deleteRoom(int room_id);
	unsigned int getRoomState(int room_id); // Return the 'isActive' variable of the room
	bool doesRoomExist(int room_id);

	// ---- Getters ----
	std::vector<RoomData> getRooms();
	Room* getRoom(int room_id);

private:
	std::map<int, Room*> m_rooms; // Map for the room and its' id
	std::map<int, OneOnOne*> m_oneOnOne_rooms;
	OneOnOne* currRoom;
};
