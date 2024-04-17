#pragma once
#include "Communicator.h"
#include "IRequestHandler.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handleFactory, std::string roomAdmin, RoomManager& roomManager);
	virtual bool isRequestRelevant(RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo& reqInfo) override;
private:

	RequestResult closeRoom(RequestInfo& reqInfo);
	RequestResult startGame(RequestInfo& reqInfo);
	RequestResult getRoomState(RequestInfo& reqInfo);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};

