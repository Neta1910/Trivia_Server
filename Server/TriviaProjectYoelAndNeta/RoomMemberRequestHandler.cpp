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
	return (reqInfo.RequestId == LEAVE_ROOM_REQ || reqInfo.RequestId == GET_ROOM_STATE_REQ);
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
