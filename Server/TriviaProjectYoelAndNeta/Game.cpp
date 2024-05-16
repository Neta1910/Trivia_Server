#include "Game.h"

//Game::Game(Game& game)
//{
//    this->m_questions = game.m_questions;
//    this->m_players = game.m_players;
//    this->gameId = game.gameId;
//}
//
//Game::Game(GameData& game_data)
//{
//    this->
//}

Game::Game(const std::vector<Question> questions, const std::vector<LoggedUser> players, const  unsigned int gameId)
{    
    for (auto& question : questions)
    {
        this->m_questions.push_back(question);
    }

    for (auto& logged_user : players)
    {
        GameData new_gameData{ m_questions[0], 0,0,0 };
        this->m_players.insert({ logged_user, new_gameData });
    }
    this->m_gameId = gameId;
}

Question Game::getQuestionForUser(LoggedUser user)
{
    for (auto& it : this->m_players) // Find the needed player and return the current question
    {
        if (it.first.getUsername() == user.getUsername())
        {
            return it.second.currentQuestion;
        }
    }
    return Question("", std::vector<std::string>(), ""); // Return an empty question if the wanted user was not found
}

void Game::submitAnswer(LoggedUser user, unsigned int answer)
{
    GameData* game_data = NULL;
    // Search for needed player
    for (auto it : this->m_players)
    {
        if (it.first.getId() == user.getId())
        {
            game_data = &it.second;
        }
    }

    if (game_data != NULL) // If player was found
    {
        if (answer == CORRECT_ANS)
        {
            game_data->correctAnswerCount++;
        }
        else
        {
            game_data->wrongAnswerCount++;
        }
        // Find index of current question and move on to the next one
        int curr_q_index = 0;
        for (curr_q_index = 0; curr_q_index < m_questions.size(); curr_q_index++)
        {
            if (game_data->currentQuestion == m_questions[curr_q_index])
            {
                break;
            }
        }
        game_data->currentQuestion = m_questions[curr_q_index + 1]; // Assign next question
    }

}

void Game::removePlayer(LoggedUser user)
{
    std::map<LoggedUser, GameData>::iterator it = m_players.find(user);
    if (it != m_players.end())
    {
        m_players.erase(it);
    }
}

bool Game::areAllPlayersDonePlaying()
{
    std::map<LoggedUser, GameData>::iterator it;
    for (it = m_players.begin(); it != m_players.end(); ++it)
    {
        if ((*it).second.currentQuestion != m_questions.back())
        {
            return false;
        }
    }
    return true;
}

std::map<LoggedUser, GameData> Game::getAllPlayers()
{
    return m_players;
}

int Game::getGameId()
{
    return m_gameId;
}

void Game::submitGameStatsToDB(GameData game_data)
{
    if (areAllPlayersDonePlaying())
    {
        for (const auto& it : m_players) 
        {
            m_database->submitGameStatistics(game_data, it.first.getId());
        }        
    }
}

bool Game::isCurrQuestionLast(LoggedUser user)
{
    // Find current question for user
    for (auto it : m_players)
    {
        if (it.second.currentQuestion == m_questions[m_questions.max_size()])
        {
            return true;
        }
    }
    return false;
}
