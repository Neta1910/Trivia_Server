#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handleFactory, std::string username, RoomManager roomManager);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handleFactory;
	RoomManager& m_roomManager;


	RequestResult logOut(RequestInfo& reqInfo);
	RequestResult getRooms(RequestInfo& reqInfo);
	RequestResult getPlayersInRoom(RequestInfo& reqInfo);
	RequestResult getPersonalStats(RequestInfo& reqInfo);
	RequestResult getHighScore(RequestInfo& reqInfo);
	RequestResult joinRoom(RequestInfo& reqInfo);
	RequestResult createRoom(RequestInfo& reqInfo);
};
