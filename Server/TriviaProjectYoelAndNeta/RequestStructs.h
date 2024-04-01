#pragma once
#include "pch.h"
#include "IRequestHandler.h"

struct LoginRequest
{
	std::string userName;
	std::string password;
} typedef LoginRequest;


struct SignUpRequest
{
	std::string userName;
	std::string password;
	std::string email;
} typedef SignUpRequest;

struct RequestResult
{
	std::vector<BYTE> response;
	IRequestHandler* newHandler;
} typedef RequestResult;

struct RequestInfo
{
	int RequestId;
	std::time_t receivalTime;
	std::vector<BYTE> buffer;
} typedef RequestInfo;