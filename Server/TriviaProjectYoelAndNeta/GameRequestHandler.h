#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class RequestHandlerFactory;
//class GameManager;


class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handleFactory, GameManager& m_gameManager, LoggedUser user, Game& game);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	GameManager& m_gameManager; 
	LoggedUser m_user;
	Game& m_game;

	RequestResult getQuestion(RequestInfo reqInfo);
	RequestResult submitAnswer(RequestInfo reqInfo);
	RequestResult getGameResults(RequestInfo reqInfo);
	RequestResult leaveGame(RequestInfo reqInfo);
};
