#pragma once
#include "RequestStructs.h"
#include "pch.h"

class IRequestHandler
{
public: 
	IRequestHandler(); 
	virtual bool isRequestRelevant(RequestInfo& reqInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo& reqInfo) = 0;
};