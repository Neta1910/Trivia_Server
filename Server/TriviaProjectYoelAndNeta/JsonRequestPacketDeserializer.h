#pragma once
#include "RequestStructs.h"
#include "json.hpp"

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:

	static JsonRequestPacketDeserializer& getInstance()
	{
		static JsonRequestPacketDeserializer instance;
		return instance;
	}

	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignUpRequest(const std::vector<unsigned char> buffer);
	static int convertUnsignedToInt(const std::vector<unsigned char>& buffer);
};
