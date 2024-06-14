#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handleFactory, LoggedUser* member, RoomManager& roomManager, Room* room) :
	m_handleFactory(handleFactory),
	m_user(member),
	m_roomManager(roomManager),
	m_room(room)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == LEAVE_ROOM_REQ || reqInfo.RequestId == GET_ROOM_STATE_REQ || reqInfo.RequestId == GET_PLAYERS_REQ || reqInfo.RequestId == AM_I_ADMIN_REQ || reqInfo.RequestId == LOGOUT_REQ);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo& reqInfo)
{
	switch (reqInfo.RequestId)
	{
	case LEAVE_ROOM_REQ:
		return leaveRoom(reqInfo);
		break;
	case GET_ROOM_STATE_REQ:
		return getRoomState(reqInfo);
		break;
	case GET_PLAYERS_REQ:
		return this->getPlayersInRoom(reqInfo);
		break;
	case AM_I_ADMIN_REQ:
		return this->amIAdmin(reqInfo);
	case LOGOUT_REQ:
		return this->logOut(reqInfo);
	}
}

void RoomMemberRequestHandler::setUpdated(const bool& val)
{
	for (auto it : this->m_room->getAllLoggedUsers())
	{
		it->setUpdateInOwnRoom(val);
	}
}

RequestResult RoomMemberRequestHandler::amIAdmin(RequestInfo& requInfo)
{
	AmIAdminResponse amIAdmin_res{ WORKING_STATUS, false };
	return { JsonResponsePacketSerialize::serializeAmIAdminResponse(amIAdmin_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(m_user, m_room) };
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo reqInfo)
{
	LeaveRoomResponse leaveRoom_res = { WORKING_STATUS };
	m_roomManager.getRoom(m_room->getRoomData().id)->removeUser(m_user);
	this->setUpdated(true);
	return { JsonResponsePacketSerialize::serializeLeaveRoomResponse(leaveRoom_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo& reqInfo)
{
	if (this->m_user->getUpdateInOwnRoom())
	{
		GetRoomStateResponse getRoomState_res{ WORKING_STATUS, m_room->getRoomData().isGameBegun, m_room->getAllUsers(), m_room->getRoomData().numOfQuestionsInGame, m_room->getRoomData().timePerQuestion };
		this->m_user->setUpdateInOwnRoom(false);
		if (m_room->getRoomData().isGameBegun)
		{
			return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handleFactory.createGameRequestHandler(m_user, m_handleFactory.getGameManager().getGame(m_room->getRoomData().game_id))};
		}
		if (!m_room->getRoomData().isActive)
		{
			getRoomState_res.status = INACTIVE_ROOM_STATUS;
			return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
		}
		return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(m_user, m_room) };
	}
	else
	{
		GetRoomStateResponse getRoomState_res;
		getRoomState_res.status = NOT_SOMTHING_TO_UPDATE;
		return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(m_user, m_room) };
	}
}

RequestResult RoomMemberRequestHandler::getPlayersInRoom(RequestInfo& reqInfo)
{
	GetPlayersInRoomRequest getPlayersInRoom_req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(reqInfo.buffer);
	if (!m_roomManager.doesRoomExist(getPlayersInRoom_req.roomId))
	{
		ErrorResponse error_res = { "Room doesn't exist" };
		return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(m_user, m_room) };
	}
	GetPlayersInRoomResponse getPlayersRoom_res = { WORKING_STATUS, m_roomManager.getRoom(getPlayersInRoom_req.roomId)->getAllUsers() };
	return { JsonResponsePacketSerialize::serializeGetPlayersInRoomResponse(getPlayersRoom_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(m_user, m_room) };
}

RequestResult RoomMemberRequestHandler::logOut(RequestInfo& reqInfo)
{
	LoginManager::getInstance(this->m_handleFactory.getDatabase()).logout(m_user->getUsername());
	LogoutResponse logOut_res = { WORKING_STATUS };
	return { JsonResponsePacketSerialize::serializeLogoutResponse(logOut_res), (IRequestHandler*)m_handleFactory.createLoginRequestHandler() };
}
