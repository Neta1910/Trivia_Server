#include "Game.h"


Game::Game(const std::vector<Question> questions, const std::vector<LoggedUser*> players, const  unsigned int gameId, IDatabase* db) : m_database(db)
{    
    for (auto& question : questions)
    {
        this->m_questions.push_back(question);
    }


    for (auto logged_user : players)
    {
        GameData* new_gameData = new GameData{ m_questions[0], 0,0,0 };
        std::pair<LoggedUser*, GameData*> new_pair(logged_user, new_gameData);
        this->m_players.insert(new_pair);
        this->m_question_of_user.insert({ logged_user, 0 });
    }


    this->m_gameId = gameId;
}

Question Game::getQuestionForUser(LoggedUser* user)
{
    return this->m_questions[this->m_question_of_user.find(user)->second];
}

int Game::submitAnswer(LoggedUser* user, unsigned int answer)
{
    GameData* game_data = NULL;


    // Search for needed player
    for (auto it : this->m_players)
    {
        if (it.first->getId() == user->getId())
        {
            game_data = it.second;
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
        if (m_question_of_user[user] == m_questions.size() - 1)
        {
            return USER_ENDED_GAME;
        }
        this->m_question_of_user[user]++;
    }


    return 1;
}

void Game::removePlayer(LoggedUser* user)
{
    std::map<LoggedUser*, GameData*>::iterator it;
    for (it = m_players.begin(); it != m_players.end(); ++it)
    {
        if ((*it).first->getUsername() == user->getUsername())
        {
            m_players.erase(it);
        }
    }
    if (it == m_players.end()) // Return error if user isn't a player
    {
        throw std::exception(USER_NOT_A_PLAYER + user->getId());
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

std::map<LoggedUser*, GameData*> Game::getAllPlayers()
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
        for (auto& it : m_players) 
        {
            m_database->submitGameStatistics(game_data, *(it.first));
        }        
    }
}

bool Game::isCurrQuestionLast(LoggedUser user)
{
    // Find current question for user
    for (auto it : m_players)
    {
        if (it.second->currentQuestion == m_questions[m_questions.max_size()])
        {
            return true;
        }
    }
    return false;
}
