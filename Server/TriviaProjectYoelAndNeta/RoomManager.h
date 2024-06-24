#pragma once
#include <map>
#include "Room.h"
#include "OneOnOneRoom.h"
#include "pch.h"

class RoomManager
{
public:
	RoomManager() { 
		currRoom = new OneOnOne(0);
	};

	int createRoom(LoggedUser* logged_user, RoomData room_data);
	void deleteRoom(int room_id);
	unsigned int getRoomState(int room_id); // Return the 'isActive' variable of the room
	bool doesRoomExist(int room_id);

	// ---- Getters ----
	std::vector<RoomData> getRooms();
	Room* getRoom(int room_id);
	OneOnOne* getCurr();
	void createNewCurr();
private:
	std::map<int, Room*> m_rooms; // Map for the room and its' id
	OneOnOne* currRoom;
	mutable std::mutex m_rooms_mutex;
};
