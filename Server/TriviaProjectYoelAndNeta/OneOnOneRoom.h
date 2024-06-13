#pragma once
#include "LoggedUser.h"
#include "Room.h"
class OneOnOne : public Room {
public:
	OneOnOne(int room_id);
	bool isRoomFull() const;
	void addUser(LoggedUser* logged_user);
};
