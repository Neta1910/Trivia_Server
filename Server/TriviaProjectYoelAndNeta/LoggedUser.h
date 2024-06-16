#pragma once
#include <iostream>
#include "WinSock2.h"

class LoggedUser
{
public:
	LoggedUser(std::string username, const int& id);
	std::string getUsername() const ;
	int getId() const;
	SOCKET getSocket();
	bool operator==(const LoggedUser& other);
	bool operator<(const LoggedUser& other) const;

	void setUpdateInOwnRoom(const bool& val);
	void setUpdateInRooms(const bool& val);

	bool getUpdateInOwnRoom() const;
	bool getUpdateInRooms() const;


private:
	std::string m_username;
	int user_id;
	SOCKET m_socket;
	bool _isUpdatedInRooms;
	bool _isUpdatedInHisOwnRoom;
};
