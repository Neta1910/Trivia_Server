#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	static LoginRequestHandler& getInstance(RequestHandlerFactory& handleFactory)
	{
		static LoginRequestHandler instance(handleFactory);
		return instance;
	}

	LoginRequestHandler(RequestHandlerFactory& handleFactory);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;
private:
	RequestHandlerFactory& m_handleFactory;
};
