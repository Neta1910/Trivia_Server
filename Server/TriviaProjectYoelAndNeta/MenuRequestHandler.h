#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handleFactory, std::string username);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;

	RequestResult signOut(RequestResult& reqInfo);
	RequestResult getRooms(RequestResult& reqInfo);
	RequestResult getPlayersInRoom(RequestResult& reqInfo);
	RequestResult getPersonalStats(RequestResult& reqInfo);
	RequestResult getHighScore(RequestResult& reqInfo);
	RequestResult joinRoom(RequestResult& reqInfo);
	RequestResult createRoom(RequestResult& reqInfo);

private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handleFactory;
};
