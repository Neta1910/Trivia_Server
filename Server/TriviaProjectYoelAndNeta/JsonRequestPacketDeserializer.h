#pragma once
#include "RequestStructs.h"
#include "json.hpp"
#include "pch.h"
#include <iostream>
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

	// v1
	static LoginRequest deserializeLoginRequest(const std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignUpRequest(const std::vector<unsigned char> buffer);


	// v2
	static LoginRequest deserializeGetPlayersInRoomRequest(const std::vector<unsigned char> buffer);
	static LoginRequest deserializeJoinRoomRequest(const std::vector<unsigned char> buffer);
	static LoginRequest deserializeCreateRoomRequest(const std::vector<unsigned char> buffer);

	// general
	static int convertUnsignedToInt(const std::vector<unsigned char>& buffer);
private:
	JsonRequestPacketDeserializer() {};
};
