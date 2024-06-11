#pragma once

#include <iostream>
#include <vector>

class ICryptoAlgorithm
{
public:
	virtual std::vector<unsigned char> decrypt(const std::vector<unsigned char>& client_message) const = 0;
	virtual std::vector<unsigned char> encrypt(const std::vector<unsigned char>& client_message) const = 0;
};