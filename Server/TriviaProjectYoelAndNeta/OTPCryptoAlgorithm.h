#pragma once
#include "ICryptoAlgorithm.h"

class OTPCryptoAlgorithm : public ICryptoAlgorithm
{
public:
	virtual std::vector<unsigned char> decrypt(const std::vector<unsigned char> client_message) const override;
	virtual std::vector<unsigned char> encrypt(const std::vector<unsigned char> client_message) const override;
};
