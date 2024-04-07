#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager GetLoginManager();
private: 
	LoginManager m_loginManager;
	IDatabase* m_database;
};
