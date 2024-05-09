#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    return (reqInfo.RequestId == GET_QUESTION_REQ ||
        reqInfo.RequestId == SUBMIT_ANSWER_REQ ||
        reqInfo.RequestId == GET_GAME_RESULT_REQ ||
        reqInfo.RequestId == LEAVE_GAME_REQ);
}

RequestResult GameRequestHandler::handleRequest(RequestInfo reqInfo)
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
    return RequestResult();
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

