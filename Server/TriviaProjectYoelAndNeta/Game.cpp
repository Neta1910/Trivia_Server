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

    for (LoggedUser logged_user : players)
    {
        GameData new_gameData{ m_questions[0], 0,0,0 };
        std::pair<LoggedUser, GameData> new_pair(logged_user, new_gameData);
        this->m_players.insert(new_pair);
        this->m_question_of_user.insert({ logged_user, 0 });
    }
    this->m_gameId = gameId;
}

Question Game::getQuestionForUser(LoggedUser user)
{
    return this->m_questions[this->m_question_of_user.find(user)->second];
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
        this->m_question_of_user[user]++;
    }

}

void Game::removePlayer(LoggedUser user)
{
    //std::map<LoggedUser, GameData>::iterator it = m_players.find(user);
    //if (it != m_players.end())
    //{
    //    m_players.erase(it);
    //}
    std::map<LoggedUser, GameData>::iterator it;
    for (it = m_players.begin(); it != m_players.end(); ++it)
    {
        if ((*it).first.getUsername() == user.getUsername())
        {
            m_players.erase(it);
        }
    }

}

bool Game::areAllPlayersDonePlaying()
{
    for (auto it : m_question_of_user)
    {
        if (it.second < m_questions.size() - 1)
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
