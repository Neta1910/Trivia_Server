#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RequestHandlerFactory;
class userStats;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handleFactory, LoggedUser* user, RoomManager& roomManager);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;
	static std::vector<std::string> statsToVector(userStats user_stats);
	static std::vector<std::string> highestScoreToVector(std::vector<HighestScore>& highest_scores);
	void setUpdateOfUsers(const bool& val);

private:
	LoggedUser* m_user;
	RequestHandlerFactory& m_handleFactory;
	RoomManager& m_roomManager;


	RequestResult logOut(RequestInfo& reqInfo);
	RequestResult getRooms(RequestInfo& reqInfo);
	RequestResult getPersonalStats(RequestInfo& reqInfo);
	RequestResult getHighScore(RequestInfo& reqInfo);
	RequestResult joinRoom(RequestInfo& reqInfo);
	RequestResult createRoom(RequestInfo& reqInfo);
};
