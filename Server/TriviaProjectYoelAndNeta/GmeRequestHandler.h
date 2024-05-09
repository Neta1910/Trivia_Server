#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class GmeRequestHandler : public IRequestHandler
{
public:
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
