#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username, const int& id)
{
	this->m_username = username;
	this->user_id = id;
	this->_isUpdatedInHisOwnRoom = true;
	this->_isUpdatedInRooms = true;
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

void LoggedUser::setUpdateInOwnRoom(const bool& val)
{
	this->_isUpdatedInHisOwnRoom = val;
}

void LoggedUser::setUpdateInRooms(const bool& val)
{
	this->_isUpdatedInRooms = val;
}

bool LoggedUser::getUpdateInOwnRoom() const
{
	return this->_isUpdatedInHisOwnRoom;
}

bool LoggedUser::getUpdateInRooms() const
{
	return this->_isUpdatedInRooms;
}
