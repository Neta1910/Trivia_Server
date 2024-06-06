#pragma once
#include "Communicator.h"
#include "IRequestHandler.h"
#include "Room.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handleFactory, LoggedUser* roomAdmin, RoomManager& roomManager, Room* room);
	virtual bool isRequestRelevant(RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo& reqInfo) override;
private:

	RequestResult closeRoom(RequestInfo& reqInfo);
	RequestResult startGame(RequestInfo& reqInfo);
	RequestResult getRoomState(RequestInfo& reqInfo);
	RequestResult amIAdmin(RequestInfo& requInfo);
	RequestResult getPlayersInRoom(RequestInfo& reqInfo);
	void setUpdated(const bool& val);

	Room* m_room;
	LoggedUser* m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};

