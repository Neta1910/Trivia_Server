#include "GameRequestHandler.h"
#include <random>

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handleFactory, GameManager& m_gameManager, LoggedUser* user, Game* game) : m_handlerFactory(handleFactory), m_gameManager(m_gameManager), m_user(user), m_game(game)
{
}

GameRequestHandler::GameRequestHandler(GameRequestHandler& other) : m_handlerFactory(other.m_handlerFactory), m_gameManager(other.m_gameManager), m_user(other.m_user), m_game(other.m_game), start(other.start), times(other.times)
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
    switch (reqInfo.RequestId)
    {
    case GET_QUESTION_REQ:
        return getQuestion(reqInfo);
        break;
    case SUBMIT_ANSWER_REQ:
        return submitAnswer(reqInfo);
        break;
    case GET_GAME_RESULT_REQ:
        return getGameResults(reqInfo);
        break;
    case LEAVE_GAME_REQ:
        return leaveGame(reqInfo);
        break;
    }
}

RequestResult GameRequestHandler::getQuestion(RequestInfo reqInfo)
{
    Question curr = m_game->getQuestionForUser(m_user);
    std::map<unsigned int, std::string> possibleAns;
    possibleAns.insert({ CORRECT_ANS_INDEX, curr.getCorrectAnswer() });
    int i = 2;
    for (auto it : curr.getPossibleAnswers())
    {
        possibleAns.insert({ i, it });
        i++;
    }

    possibleAns = shuffleAnswers(possibleAns);

    GetQuestionResponse getQuestion_res = {WORKING_STATUS, curr.getQuestion() , possibleAns };
    start = std::chrono::high_resolution_clock::now();
    return { JsonResponsePacketSerialize::serializeGetQuestionResponseResponse(getQuestion_res), (IRequestHandler*)m_handlerFactory.createGameRequestHandler(*this)};
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInfo)
{
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    this->times.push_back(duration.count());

    float sum = 0;
    // calculating avg time
    for (auto time : this->times)
    {
        sum += time;
    }
    sum /= this->times.size();

    SubmitAnswerRequest submitAns_req = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(reqInfo.buffer);
    int code = m_game->submitAnswer(m_user, submitAns_req.answerId); 

    // updating user stats:
    for (auto it : this->m_game->getAllPlayers())
    {
        if (it.first == m_user)
        {
            it.second->averageAnswerTime = sum;
            submitAns_req.answerId == CORRECT_ANS_INDEX ? it.second->correctAnswerCount++ : it.second->wrongAnswerCount++;
        }
    }

    SubmitAnswerResponse submitAnswer_res = { code, CORRECT_ANS_INDEX, sum };
    return { JsonResponsePacketSerialize::serializeSubmitAnswerResponseResponse(submitAnswer_res), (IRequestHandler*)m_handlerFactory.createGameRequestHandler(*this) };
}

RequestResult GameRequestHandler::getGameResults(RequestInfo reqInfo)
{    
    std::vector<PlayerResults> player_results;
    // If not all players are done playing, keep player in game state
    if (!m_game->areAllPlayersDonePlaying())
    {        
        return { JsonResponsePacketSerialize::serializeGetGameResultsResponseResponse({FAILED_STATUS, player_results}), (IRequestHandler*)m_handlerFactory.createGameRequestHandler(m_user, m_game)};
    }
    
    for (auto it : m_game->getAllPlayers())
    {
        player_results.push_back({ it.first->getUsername(), it.second->correctAnswerCount, it.second->wrongAnswerCount, it.second->averageAnswerTime });
    }

    std::sort(player_results.begin(), player_results.end(), [](auto& a, auto& b) {
        return a < b;
        });

    // Direct player to menu (because the game ended)
    GetGameResultsResponse gameResults_res = {WORKING_STATUS, player_results };
    return { JsonResponsePacketSerialize::serializeGetGameResultsResponseResponse(gameResults_res), (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user) };
}

RequestResult GameRequestHandler::leaveGame(RequestInfo reqInfo)
{
    LeaveGameResponse leaveGame_res = { LEAVE_GAME_RESP };
    m_game->removePlayer(m_user);
    m_gameManager.deleteGame(m_game->getGameId());
    m_handlerFactory.getRoomManager().deleteRoom(m_game->getGameId());
    return { JsonResponsePacketSerialize::serializeLeaveGameResponseResponse(leaveGame_res), (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user) };    
}


std::map<unsigned int, std::string> GameRequestHandler::shuffleAnswers(std::map<unsigned int, std::string> prev) {
    // Create a vector of pairs to hold the map elements
    std::vector<std::pair<unsigned int, std::string>> mapElements(prev.begin(), prev.end());

    // Random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector of pairs
    std::shuffle(mapElements.begin(), mapElements.end(), g);

    // Create a new map to hold the shuffled elements
    std::map<unsigned int, std::string> shuffledMap;
    for (const auto& element : mapElements) {
        shuffledMap.insert(element);
    }

    // Return the shuffled map
    return shuffledMap;
}

