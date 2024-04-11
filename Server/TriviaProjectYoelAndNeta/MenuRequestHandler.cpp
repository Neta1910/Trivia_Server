#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handleFactory, std::string username) : m_handleFactory(handleFactory), m_user(username)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == LOGOUT_REQ) ||
		(reqInfo.RequestId == GET_ROOM_REQ) ||
		(reqInfo.RequestId == GET_PLAYERS_REQ) ||
		(reqInfo.RequestId == JOIN_ROOM_REQ) ||
		(reqInfo.RequestId == CREATE_ROOM_REQ) ||
		(reqInfo.RequestId == GET_HIGH_SCORE_REQ);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& reqInfo)
{
	switch (reqInfo.RequestId)
	{
	case LOGOUT_REQ:
		return this->logOut(reqInfo);
	case GET_ROOM_REQ:
		return this->getRooms(reqInfo);
	case GET_PLAYERS_REQ:
		return this->getPlayersInRoom(reqInfo);
	case JOIN_ROOM_REQ:
		return this->joinRoom(reqInfo);
	case CREATE_ROOM_REQ:
		return this->createRoom(reqInfo);
	case GET_HIGH_SCORE_REQ:
		return this->getHighScore(reqInfo);
	}
}

RequestResult MenuRequestHandler::logOut(RequestInfo& reqInfo)
{
	LoginManager::getInstance(this->m_handleFactory.getDatabase()->doesUserExist());
}

RequestResult MenuRequestHandler::getRooms(RequestInfo& reqInfo)
{
	RequestHandlerFactory::getInstance(this->m_handleFactory.getRoomManager().getRooms());
}
