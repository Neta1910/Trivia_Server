#pragma once
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
class MenuRequestHandler
{
public:
	boolean isRequestRelevant(const RequestInfo& request);
	RequestResult handleRequest(const RequestInfo& request);
private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult signout(const RequestInfo& request);
	RequestResult getRooms(const RequestInfo& request);
	RequestResult getPlayersInRoom(const RequestInfo& request);
	RequestResult getPersonalStats(const RequestInfo& request);
	RequestResult getHighScore(const RequestInfo& request);
	RequestResult joinRoom(const RequestInfo& request);
	RequestResult createRoom(const RequestInfo& request);
};
