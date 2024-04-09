#pragma once
#include <map>
#include "Room.h"

class RoomManager
{
public:
	void createRoom(LoggedUser logged_user, RoomData room_data);
	void DeleteRoom(int room_id);
	unsigned int getRoomState(int room_id);

	// ---- Getters ----
	std::vector<Room> getRooms();
	Room& getRoom(int room_id);

private:
	std::map<int, Room> m_rooms; // Map for the room and its' id
};
