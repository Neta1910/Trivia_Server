#include "RequestHandlerFactory.h"
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db) , m_loginManager(LoginManager(db))
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
    delete m_database;
    m_database = nullptr;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::GetLoginManager()
{    
    return LoginManager::getInstance(this->m_database);
}
