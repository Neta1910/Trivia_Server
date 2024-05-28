#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "RoomData.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& handleFactory, LoggedUser member, RoomManager& roomManager, RoomData room_data);
	virtual bool isRequestRelevant(RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo& reqInfo) override;
private:

	RequestResult leaveRoom(RequestInfo reqInfo);
	RequestResult getRoomState(RequestInfo& reqInfo);
	RequestResult getPlayersInRoom(RequestInfo& reqInfo);


	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handleFactory;
};

