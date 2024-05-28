#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username, int id)
{
	this->m_username = username;
	this->user_id = id;
}

std::string LoggedUser::getUsername() const
{
	return this->m_username;
}

int LoggedUser::getId() const
{
	return user_id;
}

SOCKET LoggedUser::getSocket()
{
	return m_socket;
}

bool LoggedUser::operator==(const LoggedUser& other)
{
	return other.getUsername() == this->m_username;
}

bool LoggedUser::operator<(const LoggedUser& other) const 
{
	return this->getId() < other.getId();
}


//bool LoggedUser::operator>(const LoggedUser other)
//{
//	return false;
//}
