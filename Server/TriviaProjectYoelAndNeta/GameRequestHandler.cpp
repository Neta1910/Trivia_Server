#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handleFactory, GameManager& m_gameManager, std::string user, Game& game) : m_handlerFactory(handleFactory), m_gameManager(m_gameManager), m_user(user), m_game(game)
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
    return (reqInfo.RequestId == GET_QUESTION_REQ ||
        reqInfo.RequestId == SUBMIT_ANSWER_REQ ||
        reqInfo.RequestId == GET_GAME_RESULT_REQ ||
        reqInfo.RequestId == LEAVE_GAME_REQ);
}

RequestResult GameRequestHandler::handleRequest(RequestInfo& reqInfo)
{
    RequestResult res;
    switch (reqInfo.RequestId)
    {
    case GET_QUESTION_REQ:
        res = getQuestion(reqInfo);
        break;
    case SUBMIT_ANSWER_REQ:
        res = submitAnswer(reqInfo);
        break;
    case GET_GAME_RESULT_REQ:
        res = getGameResults(reqInfo);
        break;
    case LEAVE_GAME_REQ:
        res = leaveGame(reqInfo);
        break;
    }
    return res;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo reqInfo)
{
    std::map<unsigned int, std::string> possibleAns;
    std::vector<std::string> ans = m_game.getQuestionForUser(m_user).getPossibleAnswers();
    std::vector<std::string>::iterator it = ans.begin();
    for (int i = 0; i < NUM_OF_QUESTIONS; i++) // Assemble map of possible answers
    {
        possibleAns.insert({i + 1, (*it) });
    }
    GetQuestionResponse getQuestion_res = { GET_QUESTION_RESP,  m_game.getQuestionForUser(m_user).getQuestion() ,possibleAns };
    return { JsonResponsePacketSerialize::serializeGetQuestionResponseResponse(getQuestion_res), (IRequestHandler*)m_handlerFactory.///////////////////////////////////// };
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo reqInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(RequestInfo reqInfo)
{
    return RequestResult();
}

