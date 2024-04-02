#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler() :
	IRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == CODE_LOGIN_REQ || reqInfo.RequestId == CODE_SIGN_UP_REQ);
}
