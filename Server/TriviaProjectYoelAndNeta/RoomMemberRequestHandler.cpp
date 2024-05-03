#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handleFactory, std::string member, RoomManager& roomManager, RoomData room_data) :
	m_handleFactory(handleFactory),
	m_user(member),
	m_roomManager(roomManager),
	m_room(room_data)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == LEAVE_ROOM_REQ || reqInfo.RequestId == GET_ROOM_STATE_REQ || reqInfo.RequestId == GET_PLAYERS_REQ);
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
	case GET_PLAYERS_REQ:
		return this->getPlayersInRoom(reqInfo);
		break;
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo reqInfo)
{
	LeaveRoomResponse leaveRoom_res = { WORKING_STATUS };
	m_roomManager.getRoom(m_room.getRoomData().id).removeUser(m_user);
	return { JsonResponsePacketSerialize::serializeLeaveRoomResponse(leaveRoom_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo& reqInfo)
{
	GetRoomStateResponse getRoomState_res{ WORKING_STATUS, m_room.getRoomData().isActive, m_room.getAllUsers(), m_room.getRoomData().numOfQuestionsInGame, m_room.getRoomData().timePerQuestion };
	return { JsonResponsePacketSerialize::serializeGetRoomStateResponse(getRoomState_res), (IRequestHandler*)m_handleFactory.createRoomAdminRequestHandler(m_user, m_room) };
}

RequestResult RoomMemberRequestHandler::getPlayersInRoom(RequestInfo& reqInfo)
{
	GetPlayersInRoomRequest getPlayersInRoom_req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(reqInfo.buffer);
	if (!m_roomManager.doesRoomExist(getPlayersInRoom_req.roomId))
	{
		ErrorResponse error_res = { "Room doesn't exist" };
		return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(m_user, m_room) };
	}
	GetPlayersInRoomResponse getPlayersRoom_res = { WORKING_STATUS, m_roomManager.getRoom(getPlayersInRoom_req.roomId).getAllUsers() };
	return { JsonResponsePacketSerialize::serializeGetPlayersInRoomResponse(getPlayersRoom_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(m_user, m_room) };
}
