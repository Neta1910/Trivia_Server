#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handleFactory, std::string username, RoomManager roomManager) : 
	m_handleFactory(handleFactory), 
	m_user(username), 
	m_roomManager(roomManager)
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
	LoginManager::getInstance(this->m_handleFactory.getDatabase()).logout(m_user.getUsername());
	LogoutResponse logOut_res = { LOGOUT_RESP };
	return { JsonResponsePacketSerialize::serializeLogoutResponse(logOut_res), (IRequestHandler*)m_handleFactory.createLoginRequestHandler() };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo& reqInfo)
{
	GetRoomsResponse getRooms_res = { GET_ROOM_RESP, m_roomManager.getRooms() };
	return { JsonResponsePacketSerialize::serializeGetRoomResponse(getRooms_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo& reqInfo)
{
	//GetPlayersInRoomResponse getPlayersInRoom_res = JsonRequestPacketDeserializer::de
}
