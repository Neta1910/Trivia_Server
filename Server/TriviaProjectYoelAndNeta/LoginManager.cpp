#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* m_database)
{
	this->m_database = m_database;

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

bool LoginManager::open()
{
	return m_database->open();
}

bool LoginManager::close()
{
	return m_database->close();
}

bool LoginManager::doesUserExist(const std::string& username) 
{
	return m_database->doesUserExist(username);
}

bool LoginManager::doesPasswordMatch(const std::string& username, const std::string& password)
{
	return m_database->doesPasswordMatch(username, password);
}

bool LoginManager::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	if (!m_database->doesUserExist(username))
	{
		return m_database->addNewUser(username, password, email);
	}
	return false;
}
