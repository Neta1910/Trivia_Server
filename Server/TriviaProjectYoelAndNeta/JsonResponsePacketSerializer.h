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
	static std::vector<unsigned char> serializeErrorResponse(const  ErrorResponse& response);
	static std::vector<unsigned char> parseDataIntoMessage(const std::vector<unsigned char>& data, const int& respCode );
	static std::vector<unsigned char> turnIntToBinary(int& num, const int size);
	static void padWithZeros(std::vector<unsigned char>* data, const int& amountOfZeroz);
};
