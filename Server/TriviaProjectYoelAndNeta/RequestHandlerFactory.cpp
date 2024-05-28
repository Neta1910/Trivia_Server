#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db) , m_loginManager(db), m_statisticsManager(), m_roomManager(), m_gameManager(db)
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
    delete m_database;
    m_database = nullptr;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler( m_loginManager,*this);
}

LoginManager& RequestHandlerFactory::GetLoginManager()
{    
    return LoginManager::getInstance(this->m_database);
}

IDatabase* RequestHandlerFactory::getDatabase()
{
    return m_database;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(*this, user, this->m_roomManager);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser logged_user, Room room)
{
    return new RoomAdminRequestHandler(*this, logged_user, m_roomManager, room.getRoomData());
}

RoomMemberRequestHandler* RequestHandlerFactory::RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser logged_user, Room room)
{
    return new RoomMemberRequestHandler(*this, logged_user, m_roomManager, room.getRoomData());   
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser logged_user, Game& game)
{
    return new GameRequestHandler(*this, m_gameManager, logged_user, game);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return m_gameManager;
}
