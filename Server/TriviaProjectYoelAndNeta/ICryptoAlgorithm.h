#pragma once

#include <iostream>
#include <vector>

class ICryptoAlgorithm
{
public:
	std::vector<unsigned char> decrypt(const std::vector<unsigned char> client_message) const;
	std::vector<unsigned char> encrypt(const std::vector<unsigned char> client_message) const;
};