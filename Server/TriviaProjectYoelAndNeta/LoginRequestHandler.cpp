#include "LoginRequestHandler.h"
#include "pch.h"
#define WORK_STATUS 1
#define FAIL_STATUS 0

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handleFactory) : m_handleFactory(handleFactory), m_loginManager(loginManager)
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
		LoggedUser* user = this->m_handleFactory.GetLoginManager().login(req.userName, req.password);
		if (user) 
		{
			res.status = WORK_STATUS;
		}
		else
		{
			res.status = FAIL_STATUS;
		}
		
		MenuRequestHandler* newHandler = this->m_handleFactory.createMenuRequestHandler(user);
		return { JsonResponsePacketSerialize::serializeLoginResponse(res),  newHandler};

	}
	else if (reqInfo.RequestId = CODE_SIGN_UP_REQ)
	{
		SignUpRequest req = JsonRequestPacketDeserializer::deserializeSignUpRequest(reqInfo.buffer);
		SignupResponse res = { CODE_SIGN_UP_RESP };
		LoggedUser* user = this->m_handleFactory.GetLoginManager().signUp(req.userName, req.password, req.email, req.address, req.birthDate, req.phoneNumber);
		if (user)
		{
			MenuRequestHandler* newHandler = this->m_handleFactory.createMenuRequestHandler(user);
			res.status = WORK_STATUS;
			return { JsonResponsePacketSerialize::serializeSignUpResponse(res), newHandler };
		}
		else
		{
			LoginRequestHandler* newHandler = this->m_handleFactory.createLoginRequestHandler();
			res.status = FAIL_STATUS;
			return { JsonResponsePacketSerialize::serializeSignUpResponse(res), newHandler };
		}
	}
}
