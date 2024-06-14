#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handleFactory, LoggedUser* roomAdmin, RoomManager& roomManager, Room* room) :
	m_handlerFactory(handleFactory),
	m_user(roomAdmin),
	m_roomManager(roomManager),
	m_room(room)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == CLOSE_ROOM_REQ || reqInfo.RequestId == START_GAME_REQ || reqInfo.RequestId == GET_ROOM_STATE_REQ || reqInfo.RequestId == LEAVE_ROOM_REQ || reqInfo.RequestId == AM_I_ADMIN_REQ || reqInfo.RequestId == GET_PLAYERS_REQ  || reqInfo.RequestId == LOGOUT_REQ);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo& reqInfo)
{
	switch (reqInfo.RequestId)
	{
	case CLOSE_ROOM_REQ:
		return closeRoom(reqInfo);
		break;
	case START_GAME_REQ:
		return startGame(reqInfo);
		break;
	case GET_ROOM_STATE_REQ:
		return getRoomState(reqInfo);
		break;
	case AM_I_ADMIN_REQ:
		return amIAdmin(reqInfo);
		break;
	case GET_PLAYERS_REQ:
		return this->getPlayersInRoom(reqInfo);
		break;
	case LOGOUT_REQ:
		return this->logOut(reqInfo);
		break;
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo& reqInfo)
{
	CloseRoomResponse closeRoom_res = { WORKING_STATUS };
	m_room->getRoomData().isActive = INACTIVE_ROOM;
	this->setUpdated(true);
	return { JsonResponsePacketSerialize::serializeCloseRoomResponse(closeRoom_res), (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user) };
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo& reqInfo)
{
	StartGameResponse startGame_res = { WORKING_STATUS };
	Game* currGame = m_handlerFactory.getGameManager().createGame(m_room);
	m_room->getRoomData().game_id = currGame->getGameId();
	m_room->getRoomData().isGameBegun = true;
	this->setUpdated(true);
	return { JsonResponsePacketSerialize::serializeStartGameResponse(startGame_res), (IRequestHandler*)m_handlerFactory.createGameRequestHandler(m_user, currGame) };
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo& reqInfo)
{
	if (this->m_user->getUpdateInOwnRoom())
	{
		GetRoomStateResponse getRoomState_res{ WORKING_STATUS, m_room->getRoomData().isGameBegun, m_room->getAllUsers(), m_room->getRoomData().numOfQuestionsInGame, m_room->getRoomData().timePerQuestion };
		this->m_user->setUpdateInOwnRoom(false);
		return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room) };
	}
	else
	{
		GetRoomStateResponse getRoomState_res;
		getRoomState_res.status = NOT_SOMTHING_TO_UPDATE;
		return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room) };
	}
}

RequestResult RoomAdminRequestHandler::amIAdmin(RequestInfo& requInfo)
{
	AmIAdminResponse amIAdmin_res{ WORKING_STATUS, true};
	return { JsonResponsePacketSerialize::serializeAmIAdminResponse(amIAdmin_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room) };
}

RequestResult RoomAdminRequestHandler::getPlayersInRoom(RequestInfo& reqInfo)
{
	GetPlayersInRoomRequest getPlayersInRoom_req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(reqInfo.buffer);
	if (!m_roomManager.doesRoomExist(getPlayersInRoom_req.roomId))
	{
		ErrorResponse error_res = { "Room doesn't exist" };
		return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room)};
	}
	GetPlayersInRoomResponse getPlayersRoom_res = { WORKING_STATUS, m_roomManager.getRoom(getPlayersInRoom_req.roomId)->getAllUsers() };
	return { JsonResponsePacketSerialize::serializeGetPlayersInRoomResponse(getPlayersRoom_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room) };
}

RequestResult RoomAdminRequestHandler::logOut(RequestInfo& reqInfo)
{
	LoginManager::getInstance(this->m_handlerFactory.getDatabase()).logout(m_user->getUsername());
	LogoutResponse logOut_res = { WORKING_STATUS };
	return { JsonResponsePacketSerialize::serializeLogoutResponse(logOut_res), (IRequestHandler*)m_handlerFactory.createLoginRequestHandler() };
}

void RoomAdminRequestHandler::setUpdated(const bool& val)
{
	for (auto it : this->m_room->getAllLoggedUsers())
	{
		it->setUpdateInOwnRoom(val);
	}
}
