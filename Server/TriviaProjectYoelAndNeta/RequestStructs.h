#pragma once
#include "pch.h"

class IRequestHandler; // Forward declaration


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
	std::string address;
	std::string phoneNumber;
	std::string birthDate;
} typedef SignUpRequest;

struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
} typedef RequestResult;

struct RequestInfo
{
	int RequestId;
	std::time_t receivalTime;
	std::vector<unsigned char> buffer;
} typedef RequestInfo ;
