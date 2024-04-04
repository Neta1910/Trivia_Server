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

bool LoginManager::open()
{
	m_database->open();
}
