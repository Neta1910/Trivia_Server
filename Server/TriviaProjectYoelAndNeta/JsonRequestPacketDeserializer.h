#pragma once
#include "RequestStructs.h"
#include "json.hpp"

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const std::vector<BYTE> buffer);
	static SignUpRequest deserializeSignUpRequest(const std::vector<BYTE> buffer);
};
