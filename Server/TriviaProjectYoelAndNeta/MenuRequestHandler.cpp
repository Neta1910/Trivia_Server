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
