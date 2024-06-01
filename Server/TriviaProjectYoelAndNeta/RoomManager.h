#pragma once
#include <map>
#include "Room.h"

class RoomManager
{
public:
	RoomManager(){}

	int createRoom(LoggedUser logged_user, RoomData room_data);
	void deleteRoom(int room_id);
	unsigned int getRoomState(int room_id); // Return the 'isActive' variable of the room
	bool doesRoomExist(int room_id);
	void setUpdated(bool update);

	// ---- Getters ----
	std::vector<RoomData> getRooms();
	Room* getRoom(int room_id);
	bool getUpdated();

private:
	std::map<int, Room*> m_rooms; // Map for the room and its' id
	bool _updated;
};
