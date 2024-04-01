#pragma once
#include "pch.h"
#include "json.hpp"
#include "ResponseStructs.h"

using json = nlohmann::json;

class JsonResponsePacketSerialize
{
public:
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& response);
	static std::vector<unsigned char> serializeSignUpResponse(const SignupResponse& response);
	static std::vector<unsigned char> serializeErrorResponse(const  & response);
};
