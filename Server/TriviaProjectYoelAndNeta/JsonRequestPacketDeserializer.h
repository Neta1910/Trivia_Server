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

	// Delete copy constructor and assignment operator for singleton
	JsonRequestPacketDeserializer(JsonRequestPacketDeserializer const&) = delete;
	void operator=(JsonRequestPacketDeserializer const&) = delete;

	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignUpRequest(const std::vector<unsigned char> buffer);
	static int convertUnsignedToInt(const std::vector<unsigned char>& buffer);
private:
	JsonRequestPacketDeserializer() {};
};
