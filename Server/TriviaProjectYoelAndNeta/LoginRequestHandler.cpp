#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler() :
	IRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == CODE_LOGIN_REQ || reqInfo.RequestId == CODE_SIGN_UP_REQ);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo& reqInfo)
{
	//RequestResult req_result;
	//if (reqInfo.RequestId == CODE_LOGIN_REQ)
	//{
	//	req_result.newHandler = LoginRequest;
	//}
	//else if (reqInfo.RequestId = CODE_SIGN_UP_REQ)
	//{
	//	req_result.newHandler = SignUpRequest;
	//}
	//req_result.response = reqInfo;
}
