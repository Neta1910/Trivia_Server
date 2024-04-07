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

bool LoginManager::open()
{
	return m_database->open();
}

bool LoginManager::close()
{
	return m_database->close();
}

int LoginManager::doesUserExist(std::string username)
{
	return m_database->doesUserExist(username);
}

int LoginManager::DoesPasswordMatch(std::string username, std::string password)
{
	return m_database->DoesPasswordMatch(username, password);
}

int LoginManager::addNewUser(std::string username, std::string password, std::string email)
{
	if (!m_database->doesUserExist(username))
	{
		return m_database->addNewUser(username, password, email);
	}
	return ERROR_RETURN_CODE;
}
