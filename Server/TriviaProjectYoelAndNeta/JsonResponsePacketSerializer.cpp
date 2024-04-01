#include "JsonResponsePacketSerializer.h"

std::vector<unsigned char> JsonResponsePacketSerialize::serializeLoginResponse(const LoginResponse& response)
{
    json j = json{ {"status", response.status} };
    std::string json_str = j.dump();
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end());
    return bytes;
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeSignUpResponse(const SignupResponse& response)
{
    json j = json{ {"status", response.status} };
    std::string json_str = j.dump();
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end());
    return bytes;
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeErrorResponse(const ErrorResponse& response)
{
    json j = json{ {"message", response.message} };
    std::string json_str = j.dump();
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end());
    return bytes;
}

std::vector<unsigned char> JsonResponsePacketSerialize::parseDataIntoMessage(const std::vector<unsigned char>& data, const int& respCode)
{
    std::vector<unsigned char> res;

    // putting the code inside
    res.push_back(static_cast<unsigned char>(respCode));


    
}


