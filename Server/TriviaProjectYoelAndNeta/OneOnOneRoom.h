#pragma once
#include "LoggedUser.h"
#include "Room.h"
class OneOnOne : public Room {
public:
	OneOnOne(int room_id);
	bool isRoomFull() const;
	void addUserToRoom(LoggedUser* user);
private:
	LoggedUser* first;
	LoggedUser* second;
	unsigned int roon_id;
};
