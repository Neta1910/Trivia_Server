#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<BYTE> buffer)
{
	// Convert buffer to string
	std::string data(buffer.begin(), buffer.end());
	// Extract Json part
	data = data.substr(data.find('{'));
	json json_data = json::parse(data); // Parse to json
	return LoginRequest({ json_data[USERNAME], json_data[PASSWORD]});
}
