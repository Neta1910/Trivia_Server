#pragma once
#include "ICryptoAlgorithm.h"
#include <map>
#include "IDatabase.h"

#define HIGHEST_ASCII_VAL 125
class OTPCryptoAlgorithm : public ICryptoAlgorithm
{
public:
	OTPCryptoAlgorithm(IDatabase* db);
	virtual std::vector<unsigned char> decrypt(const std::vector<unsigned char>& client_message) const override;
	virtual std::vector<unsigned char> encrypt(const std::vector<unsigned char>& client_message) const override;
private:
	std::vector<int> getAsciiPosition(const std::vector<unsigned char>& client_message) const;
	std::vector<std::string> KeyToVal(std::vector<int>& message_as_alphabetic_positions) const;
	std::vector<unsigned char> stringVecToCharVec(std::vector<std::string>& string_vec) const;
	std::vector<int> combineVecRes(std::vector<int>& message_as_alphabetic_positions, std::vector<int>& vals_as_positions) const;
	IDatabase* m_database;
	std::map<int, std::string> _OTPKey;
};
	