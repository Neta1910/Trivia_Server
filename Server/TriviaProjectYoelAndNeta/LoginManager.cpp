#include "LoginManager.h"
#include "userCheckers.h"

LoginManager::LoginManager(IDatabase* db)
{
	this->m_database = db;

}

LoggedUser* LoginManager::signUp(const std::string& name, const std::string& password, const std::string& email, const std::string& address, const std::string& birthDate, const std::string& phoneNumber)
{
	if (m_database->doesUserExist(name))
	{
		return nullptr;
	}

	m_users_mutex.lock();
	
	// no need to check for regex in server - already checking in frontend
	m_database->addNewUser(name, password, email, address, birthDate, phoneNumber);
	int userId = m_database->getUserId(name, password);
	LoggedUser* loggedUser = new LoggedUser(name, userId);
	m_loggedUsers.push_back(loggedUser);

	m_users_mutex.unlock();
	return loggedUser;

}

LoggedUser* LoginManager::login(std::string username, std::string password)
{
	if (!m_database->doesUserExist(username)) 
	{
		return nullptr;
	}
	if (!m_database->doesPasswordMatch(username, password))
	{
		return nullptr;
	}
	// Create LoggedUser object
	int userId = m_database->getUserId(username, password);
	LoggedUser* loggedUser = new LoggedUser(username, userId);	// checking if user is already logged in m_loggedUsers
	
	if (std::find(m_loggedUsers.begin(), m_loggedUsers.end(), loggedUser) != m_loggedUsers.end())
	{
		return nullptr;
	}
	m_loggedUsers.push_back(loggedUser);
	return loggedUser;
}

bool LoginManager::logout(std::string username)
{
	m_users_mutex.lock();
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it)
	{
		if ((*it)->getUsername() == username)
		{
			LoggedUser* temp = (*it);
			it = m_loggedUsers.erase(it);
			delete temp;
			m_users_mutex.unlock();
			return true;
		}
	}
	m_users_mutex.unlock();
	return false;
}

std::vector<LoggedUser*> LoginManager::getUsers() const
{
	return this->m_loggedUsers;
}
