#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "ResponseStructs.h"

class Communicator
{
public:
	Communicator(const SOCKET& socket);
	void startHandleRequests();
	void sendData(const SOCKET sc, std::vector<unsigned char>& message, const int& flags = 0);
	std::vector<unsigned char> getDataFromSocket(const SOCKET sc, const int bytesNum, const int& flags = 0);
private:
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	void handleNewClient(const SOCKET& userSocket);

	std::vector  <unsigned char> charToUnsigned(const char* data, const int& length );
	char* unsignedToChar(const std::vector<unsigned char>& data);

	time_t getCurrentTime();
	std::mutex m_usersMu;
};
