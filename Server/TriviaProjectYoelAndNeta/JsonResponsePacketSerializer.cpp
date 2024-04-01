#include "JsonResponsePacketSerializer.h"

std::vector<unsigned char> JsonResponsePacketSerialize::serializeLoginResponse(const LoginResponse& response)
{
    json j = json{ {"name", response.status} };
    std::string json_str = j.dump();
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end());
    return bytes;
}
