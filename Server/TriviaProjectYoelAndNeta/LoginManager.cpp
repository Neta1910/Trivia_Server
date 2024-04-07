#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db)
{
	this->m_database = db;

}

bool LoginManager::signUp(std::string username, std::string password, std::string email)
{
	if (m_database->doesUserExist(username))
	{
		return false;
	}
	m_database->addNewUser(username, password, email);
	return true;
}

bool LoginManager::login(std::string username, std::string password)
{
	if (!m_database->doesUserExist(username)) 
	{
		return false;
	}
	if (m_database->doesPasswordMatch(username, password))
	{
		return false;
	}
	// Create LoggedUser object
	LoggedUser loggedUser(username);	// checking if user is already logged in m_loggedUsers
	if (std::find(m_loggedUsers.begin(), m_loggedUsers.end(), loggedUser) != m_loggedUsers.end())
	{
		return false;
	}

	m_loggedUsers.push_back(loggedUser);
	return true;
}

bool LoginManager::logout(std::string username)
{
	int counter = 0;
	std::vector<LoggedUser>::iterator it;
	for (it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it)
	{
		if ((*it).getUsername() == username)
		{
			m_loggedUsers.erase(it);
		}
		counter++;
	}
	return true;
}
