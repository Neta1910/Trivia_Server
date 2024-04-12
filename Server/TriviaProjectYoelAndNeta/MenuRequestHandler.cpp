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
	GetPlayersInRoomRequest getPlayersInRoom_req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(reqInfo.buffer);
	if (!m_roomManager.doesRoomExist(getPlayersInRoom_req.roomId))
	{
		ErrorResponse error_res = { "Room doesn't exist" };
		return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
	GetPlayersInRoomResponse getPlayersRoom_res = { GET_PLAYERS_RESP, m_roomManager.getRoom(getPlayersInRoom_req.roomId).getAllUsers() };
	return { JsonResponsePacketSerialize::serializeGetPlayersInRoomResponse(getPlayersRoom_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& reqInfo)
{
	GetPersonalStatsResponse getPersonalStats_res = { GET_PERSONAL_STATS_RESP, m_handleFactory.getStatisticsManager().getUserStatistics(m_user.getUsername()) };
	return { JsonResponsePacketSerialize::serializeGetPersonalStatsResponse(getPersonalStats_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo& reqInfo)
{
	GetHighScoreResponse getHighScore_res = { GET_HIGH_SCORE_RESP, m_handleFactory.getStatisticsManager().getHighScore() };
	return { JsonResponsePacketSerialize::serializeHighScoreResponse(getHighScore_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo& reqInfo)
{
	JoinRoomRequest joinRoom_req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);
	ErrorResponse error_res;
	if (m_roomManager.doesRoomExist(joinRoom_req.roomId))
	{
		// Check if room is full
		if (m_roomManager.getRoom(joinRoom_req.roomId).getRoomData().maxPlayers == m_roomManager.getRoom(joinRoom_req.roomId).getAllUsers().size())
		{
			error_res = { "room is full!" };
		}
		else // Join player to room if there's enough space
		{
			m_roomManager.getRoom(joinRoom_req.roomId).addUser(m_user);
			JoinRoomResponse joinRoom_res = { JOIN_ROOM_RESP };
			//return { JsonResponsePacketSerialize::serializeJoinRoomResponse(joinRoom_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler() };
		}
	}
	error_res = { "Room doesn't exist" };
	return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };

}

