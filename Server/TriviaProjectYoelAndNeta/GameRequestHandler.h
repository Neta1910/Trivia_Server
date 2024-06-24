#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"
#include <chrono>

class RequestHandlerFactory;
//class GameManager;


class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handleFactory, GameManager& m_gameManager, LoggedUser* user, Game* game);
	GameRequestHandler(GameRequestHandler& other);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	GameManager& m_gameManager; 
	LoggedUser* m_user;
	Game* m_game;
	std::chrono::high_resolution_clock::time_point answer_receival_time; // Time that the player got the question
	std::vector<float> answering_durations; // Times taken to answer a question 
	

	RequestResult getQuestion(RequestInfo reqInfo);
	RequestResult submitAnswer(RequestInfo reqInfo);
	RequestResult getGameResults(RequestInfo reqInfo);
	RequestResult leaveGame(RequestInfo reqInfo);
	RequestResult logout(RequestInfo reqInfo);
	std::map<unsigned int, std::string> shuffleAnswers(std::map<unsigned int, std::string> prev);
};
