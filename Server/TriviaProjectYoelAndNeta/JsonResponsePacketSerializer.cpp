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
    std::vector<unsigned char> code = JsonResponsePacketSerialize::turnIntToBinary(respCode);
    res.insert(res.end(), code.begin(), code.end());
    

    // getting message size 
    res.insert(res.end(), data.begin(), data.end());
    while (res.size() < MESSEGE_SIZE_TO_SIZE)
    {
        res.push_back(0);
    }

    // putting in the messege data
    res.insert(res.end(), data.begin(), data.end());

    return res;
}

std::vector<unsigned char>  JsonResponsePacketSerialize::turnIntToBinary(const int& num,const  int size)
{
    std::vector<unsigned char> binary;
    int temp = num;
    while (temp > 0) {
        int remainder = num % 2;
        binary.push_back(remainder);
        temp /= 2;
    }
    // Reverse the binary vector to get the correct binary representation
    std::reverse(binary.begin(), binary.end());
    return binary;
}

void JsonResponsePacketSerialize::padWithZeros(std::vector<unsigned char>* data, const int& amountOfZeroz)
{
    while (data->size() <= amountOfZeroz)
    {
        data->insert(data->begin(), 0);
    }
}


