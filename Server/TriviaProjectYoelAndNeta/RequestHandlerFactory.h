#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class RoomAdminRequestHandler;
class LoginManager;
class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;

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
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser logged_user, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser logged_user, Room room);


	StatisticsManager& getStatisticsManager();
private: 
	RequestHandlerFactory();

	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
};
