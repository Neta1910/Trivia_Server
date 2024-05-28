#pragma once
#include <iostream>
#include "WinSock2.h"

class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername() const ;
	int getId() const;
	SOCKET getSocket();
	bool operator==(const LoggedUser& other);
	bool operator<(const LoggedUser& other) const;
	//bool operator>(const LoggedUser other);

private:
	std::string m_username;
	int user_id;
	SOCKET m_socket;
};
