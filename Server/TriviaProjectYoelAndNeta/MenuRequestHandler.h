#pragma once
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
class MenuRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo& reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo& reqInfo) override;
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
