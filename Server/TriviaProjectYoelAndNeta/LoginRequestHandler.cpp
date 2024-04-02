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
	RequestResult req_result;
	if (reqInfo.RequestId == CODE_LOGIN_REQ)
	{
		LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);		
		LoginResponse res = { CODE_LOGIN_RESP };
		return { JsonResponsePacketSerialize::serializeLoginResponse(res), nullptr };
	}
	else if (reqInfo.RequestId = CODE_SIGN_UP_REQ)
	{
		SignUpRequest req = JsonRequestPacketDeserializer::deserializeSignUpRequest(reqInfo.buffer);
		SignupResponse res = { CODE_SIGN_UP_RESP };
		return { JsonResponsePacketSerialize::serializeSignUpResponse(res), nullptr};
	}
}
