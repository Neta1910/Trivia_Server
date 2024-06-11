#include "OTPCryptoAlgorithm.h"

OTPCryptoAlgorithm::OTPCryptoAlgorithm(IDatabase* db) : m_database(db)
{
    _OTPKey = m_database->getSecurityKey();
}

std::vector<unsigned char> OTPCryptoAlgorithm::encrypt(const std::vector<unsigned char>& client_message) const
{
    std::vector<int> message_as_alphabetic_positions = getAsciiPosition(client_message);
    std::vector<std::string> keys_as_vals = KeyToVal(message_as_alphabetic_positions);
    std::vector<unsigned char> keys_as_vals_un_ch = stringVecToCharVec(keys_as_vals);
    std::vector<int> vals_as_positions = getAsciiPosition(keys_as_vals_un_ch);
    std::vector<int> positions_added_to_vals = combineVecRes(message_as_alphabetic_positions, vals_as_positions);
    std::vector<std::string> combined_vec_encrypted = KeyToVal(positions_added_to_vals);
    return stringVecToCharVec(combined_vec_encrypted);
        
}

std::vector<int> OTPCryptoAlgorithm::getAsciiPosition(const std::vector<unsigned char>& client_message) const
{
    std::vector<int> message_as_alphabetic_positions;
    message_as_alphabetic_positions.resize(client_message.size());
    int index = 0;
    for (const unsigned char ch : client_message) // Get the alphabetic position of each char in the message
    {
        message_as_alphabetic_positions[index] = int(ch);
        index++;
    }
    return message_as_alphabetic_positions;
}

std::vector<std::string> OTPCryptoAlgorithm::KeyToVal(std::vector<int>& message_as_alphabetic_positions) const
{
    std::vector<std::string> keys_as_position;
    std::map<int, std::string>::iterator OTPKey_it;
    keys_as_position.resize(message_as_alphabetic_positions.size());
    int index = 0;
    for (int key : message_as_alphabetic_positions)
    {              
        keys_as_position[index] = (*_OTPKey.find(key)).second;
    }
    return keys_as_position;
}

std::vector<unsigned char> OTPCryptoAlgorithm::stringVecToCharVec(std::vector<std::string>& string_vec) const
{
    std::vector<unsigned char> result;
    result.resize(string_vec.size());
    for (int i = 0; i < string_vec.size(); i++)
    {
        for (int j = 0; j < string_vec[i].size(); j++)
        {
            result[i] = string_vec[i][j];
        }
    }
    return result;
}

std::vector<int> OTPCryptoAlgorithm::combineVecRes(std::vector<int>& message_as_alphabetic_positions, std::vector<int>& vals_as_positions) const
{
    std::vector<int> combinedVec;
    combinedVec.resize(message_as_alphabetic_positions.size());
    for (int i = 0; i < combinedVec.size(); i++)
    {
        combinedVec[i] = (message_as_alphabetic_positions[i] + vals_as_positions[i]) % HIGHEST_ASCII_VAL;
    }
    return combinedVec;
}
