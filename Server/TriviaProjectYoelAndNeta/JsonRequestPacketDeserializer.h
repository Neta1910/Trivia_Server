#pragma once
#include "RequestStructs.h"

class JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(char buffer[]);
	static SignUpRequest deserializeSignUpRequest(char buffer[]);
};
