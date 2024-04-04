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
	static void sendData(const SOCKET sc, std::vector<unsigned char>& message, const int& flags = 0);
	static std::string getDataFromSocket(const SOCKET sc, const int bytesNum);
private:
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	void handleNewClient(const SOCKET& userSocket);
	std::vector<BYTE> stringToBuffer(std::string str);
	time_t getCurrentTime();
	std::mutex m_usersMu;
};
