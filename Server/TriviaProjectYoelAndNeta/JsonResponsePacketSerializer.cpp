#include "JsonResponsePacketSerializer.h"
#define MESSEGE_SIZE_TO_SIZE 5
#define BYTE 8
#define CODE_LENGTH 1
#define MESSEGE_LENGTH_LENGTH 4


std::vector<unsigned char> JsonResponsePacketSerialize::serializeLoginResponse(const LoginResponse& response)
{
    json j = json{ {"status", response.status} };
    std::string json_str = j.dump();
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end());
    return JsonResponsePacketSerialize::parseDataIntoMessage(bytes, CODE_LOGIN_RESP) ;
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeSignUpResponse(const SignupResponse& response)
{
    json j = json{ {"status", response.status} };
    std::string json_str = j.dump();
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end());
    return JsonResponsePacketSerialize::parseDataIntoMessage(bytes, CODE_SIGN_UP_RESP);
}

std::vector<unsigned char> JsonResponsePacketSerialize::serializeErrorResponse(const ErrorResponse& response)
{
    json j = json{ {"message", response.message} };
    std::string json_str = j.dump();
    // Convert string to bytes
    std::vector<unsigned char> bytes(json_str.begin(), json_str.end());
    return JsonResponsePacketSerialize::parseDataIntoMessage(bytes, CODE_ERROR_RESPONSE);
}

std::vector<unsigned char> JsonResponsePacketSerialize::parseDataIntoMessage(const std::vector<unsigned char>& data, const int& respCode)
{
    std::vector<unsigned char> res;

    // putting the code inside
    std::vector<unsigned char> code = JsonResponsePacketSerialize::turnIntToBytes(respCode);
    for (int i = 0; i < code.size() + 1; i++)
    {
        code.pop_back();
    }
    res.insert(res.end(), code.begin(), code.end());
    

    // getting message size 
    std::vector<unsigned char> sizeOfMessage = JsonResponsePacketSerialize::turnIntToBytes(data.size());
    res.insert(res.end(), sizeOfMessage.begin(), sizeOfMessage.end());
    

    // putting in the messege data
    res.insert(res.end(), data.begin(), data.end());

    return res;
}

std::vector<unsigned char> JsonResponsePacketSerialize::turnIntToBytes(const int& num)
{
    std::vector<unsigned char> bytes(sizeof(int));

    for (size_t i = 0; i < sizeof(int); ++i) {
        bytes[i] = static_cast<unsigned char>((num >> (i * 8)) & 0xFF);
    }

    return bytes;
}

void JsonResponsePacketSerialize::padWithZeros(std::vector<unsigned char>* data, const int& amountOfZero)
{
    while (data->size() <= amountOfZero)
    {
        data->insert(data->begin(), 0);
    }
}


