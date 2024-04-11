#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handleFactory, std::string username) : m_handleFactory(handleFactory), m_user(username)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == )
}
