#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handleFactory);
	bool isRequestRelevant(RequestInfo& reqInfo) override;
	RequestResult handleRequest(RequestInfo& reqInfo) override;
private:
	RequestHandlerFactory& m_handleFactory;
};
