#include "JsonRequestPacketDeserializer.h"
#define LENGTH_PART_END 5
#define JSON_START 6
#define SHIFT 5
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char> buffer)
{
	// Convert buffer to string
	std::vector <unsigned char> copyCharConsistingOfLength(buffer.begin() + 1, buffer.begin() + LENGTH_PART_END);
	int messageSize = JsonRequestPacketDeserializer::convertUnsignedToInt(copyCharConsistingOfLength);
	std::string data(buffer.begin() + LENGTH_PART_END, buffer.begin() + messageSize + SHIFT);
	// Extract Json part
	data = data.substr(data.find('{'));
	json json_data = json::parse(data); // Parse to json
	std::cout << json_data[USERNAME] << ", " << json_data[PASSWORD];
	return LoginRequest({ json_data[USERNAME], json_data[PASSWORD]});
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const std::vector<unsigned char> buffer)
{
	// Convert buffer to string
	std::string data(buffer.begin(), buffer.end());
	// Extract Json part
	data = data.substr(data.find('{'));
	json json_data = json::parse(data); // Parse to json
	return SignUpRequest({ json_data[USERNAME], json_data[PASSWORD], json_data[EMAIL]});
}

int JsonRequestPacketDeserializer::convertUnsignedToInt(const std::vector<unsigned char>& buffer)
{
	// Convert bytes to integer
	int result = 0;
	for (size_t i = 0; i < buffer.size(); ++i) {
		result = (result << 8) | buffer[i];
	}
	return result;
}
