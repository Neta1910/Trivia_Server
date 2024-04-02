#pragma once
#include "RequestStructs.h"

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo reqInfo);
	virtual RequestResult handleRequest(RequestInfo reqInfo);
};