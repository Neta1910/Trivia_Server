#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db)
{
	this->m_database = db;

}

void LoginManager::signUp(std::string username, std::string password, std::string email)
{
	m_database->addNewUser(username, password, email);
}

void LoginManager::login(std::string username, std::string password)
{
	if (!m_database->doesUserExist(username))
	{
		return;
	}
	// Create LoggedUser object
	LoggedUser loggedUser(username);
	m_loggedUsers.push_back(loggedUser);
}

void LoginManager::logout(std::string username)
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
}