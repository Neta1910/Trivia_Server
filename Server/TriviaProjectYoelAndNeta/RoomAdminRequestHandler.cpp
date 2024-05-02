#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handleFactory, std::string roomAdmin, RoomManager& roomManager, RoomData room_data) :
	m_handlerFactory(handleFactory),
	m_user(roomAdmin),
	m_roomManager(roomManager),
	m_room(room_data)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == CLOSE_ROOM_REQ || reqInfo.RequestId == START_GAME_REQ || reqInfo.RequestId == GET_ROOM_STATE_REQ || reqInfo.RequestId == LEAVE_ROOM_REQ || reqInfo.RequestId == AM_I_ADMIN_REQ);
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
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo& reqInfo)
{
	CloseRoomResponse closeRoom_res = { CLOSE_ROOM_RESP };
	// Send LeaveRoomResponse to all room members
	for (auto roomMembers : m_room.getAllLoggedUsers())
	{
		LeaveRoomResponse leaveRoom_res = { WORKING_STATUS };
		m_roomManager.getRoom(m_room.getRoomData().id).removeUser(roomMembers);
		std::vector<unsigned char> serialized_res = JsonResponsePacketSerialize::serializeLeaveRoomResponse(leaveRoom_res);
		Communicator::sendData(roomMembers.getSocket(), serialized_res);
	}
	m_roomManager.DeleteRoom(m_room.getRoomData().id);
	return { JsonResponsePacketSerialize::serializeCloseRoomResponse(closeRoom_res), (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user) };
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo& reqInfo)
{
	StartGameResponse startGame_res = { WORKING_STATUS };
	for (auto roomMembers : m_room.getAllLoggedUsers())
	{
		std::vector<unsigned char> serialized_res = JsonResponsePacketSerialize::serializeStartGameResponse(startGame_res);
		Communicator::sendData(roomMembers.getSocket(), serialized_res);
	}
	// !!!!!!!!!!!!!!!!! NOTE !!!!!!!!!!!!!!!!!
	// Line 56 is not yet returning the right handler, it's supposed to create a game room, which will be supported in the next versions.
	return { JsonResponsePacketSerialize::serializeStartGameResponse(startGame_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room) };
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo& reqInfo)
{
	GetRoomStateResponse getRoomState_res{ WORKING_STATUS, m_room.getRoomData().isActive, m_room.getAllUsers(), m_room.getRoomData().numOfQuestionsInGame, m_room.getRoomData().timePerQuestion };
	return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room) };
}

RequestResult RoomAdminRequestHandler::amIAdmin(RequestInfo& requInfo)
{
	AmIAdminResponse amIAdmin_res{ WORKING_STATUS, m_room.getRoomData().roomAdmin == m_user.getId()};
	return { JsonResponsePacketSerialize::serializeAmIAdminResponse(amIAdmin_res), (IRequestHandler*)m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room) };
}
