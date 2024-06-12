#include "OneOnOneRoom.h"

OneOnOne::OneOnOne(int room_id) : first(nullptr), second(nullptr), roon_id(room_id)

{
}

bool OneOnOne::isRoomFull() const
{
	return second != nullptr ? true : false;
}

void OneOnOne::addUserToRoom(LoggedUser* user)
{
	if (first == nullptr)
	{
		first = user;
	}
	else
	{
		second = user;
	}
}
