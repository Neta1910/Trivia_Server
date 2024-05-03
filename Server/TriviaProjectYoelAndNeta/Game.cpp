#include "Game.h"

Game::Game(Game& game)
{
    this->m_questions = game.m_questions;
    this->m_players = game.m_players;
    this->gameId = game.gameId;
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
    for (auto it : this->m_players)
    {

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

void Game::submitGameStatsToDB(GameData game_data)
{

}

bool Game::isCurrQuestionLast(LoggedUser user)
{
    // Find current question for user
    /*for (auto it : m_players)
    {
        if (it.second.currentQuestion == m_questions[m_questions.max_size()])
        {

        }
    }*/
}
