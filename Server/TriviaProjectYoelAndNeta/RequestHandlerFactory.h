#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"

class LoginManager;
class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	static RequestHandlerFactory& getInstance(IDatabase* db)
	{
		static RequestHandlerFactory instance(db);
		return instance;
	}

	// Delete copy constructor and assignment operator for singleton
	RequestHandlerFactory(RequestHandlerFactory const&) = delete;
	void operator=(RequestHandlerFactory const&) = delete;

	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& GetLoginManager();

	IDatabase* getDatabase();
	RoomManager& getRoomManager();

private: 

	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
		
};
