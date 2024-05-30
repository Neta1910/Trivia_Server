#include "GameRequestHandler.h"
#include <random>

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handleFactory, GameManager& m_gameManager, LoggedUser user, Game& game) : m_handlerFactory(handleFactory), m_gameManager(m_gameManager), m_user(user), m_game(game)
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
    Question curr = m_game.getQuestionForUser(m_user);
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
    return { JsonResponsePacketSerialize::serializeGetQuestionResponseResponse(getQuestion_res), (IRequestHandler*)m_handlerFactory.createGameRequestHandler(m_user, m_game)};
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInfo)
{
    SubmitAnswerRequest submitAns_req = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(reqInfo.buffer);
    m_game.submitAnswer(m_user, submitAns_req.answerId); 
    SubmitAnswerResponse submitAnswer_res = { WORKING_STATUS, CORRECT_ANS_INDEX };
    return { JsonResponsePacketSerialize::serializeSubmitAnswerResponseResponse(submitAnswer_res), (IRequestHandler*)m_handlerFactory.createGameRequestHandler(m_user, m_game) };
}

RequestResult GameRequestHandler::getGameResults(RequestInfo reqInfo)
{    
    std::vector<PlayerResults> player_results; 

    // If not all players are done playing, keep player in game state
    if (!m_game.areAllPlayersDonePlaying())
    {        
        return { JsonResponsePacketSerialize::serializeGetGameResultsResponseResponse({WORKING_STATUS, player_results}), (IRequestHandler*)m_handlerFactory.createGameRequestHandler(m_user, m_game)};
    }
    
    std::map<LoggedUser, GameData> all_players = m_game.getAllPlayers();
    std::map<LoggedUser, GameData>::iterator players_it;
    std::vector<PlayerResults>::iterator results_it = player_results.begin(); 

    for (players_it = all_players.begin(); players_it != all_players.end(); ++players_it) // Assemble vector of 'PlayerResults'
    {
        (*results_it).averageAnswerTime = (*players_it).second.averageAnswerTime;
        (*results_it).wrongAnswerCount = (*players_it).second.wrongAnswerCount;
        (*results_it).correctAnswerCount = (*players_it).second.correctAnswerCount;
        (*results_it).username = (*players_it).first.getUsername();
        ++results_it;
    }
    // Direct player to menu (because the game ended)
    GetGameResultsResponse gameResults_res = { GET_GAME_RESULTS_RESP, player_results };
    return { JsonResponsePacketSerialize::serializeGetGameResultsResponseResponse(gameResults_res), (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user) };
}

RequestResult GameRequestHandler::leaveGame(RequestInfo reqInfo)
{
    LeaveGameResponse leaveGame_res = { LEAVE_GAME_RESP };
    m_game.removePlayer(m_user);
    m_gameManager.deleteGame(m_game.getGameId());
    m_handlerFactory.getRoomManager().DeleteRoom(m_game.getGameId());
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

