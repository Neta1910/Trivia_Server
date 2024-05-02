#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "RoomData.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& handleFactory, std::string member, RoomManager& roomManager);
	virtual bool isRequestRelevant(RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo& reqInfo) override;
private:

	RequestResult leaveRoom(RequestInfo reqInfo);
	RequestResult getRoomState(RequestInfo& reqInfo);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handleFactory;
};

