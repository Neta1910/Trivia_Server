#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "Helper.h"

class Communicator
{
public:
	void startHandleRequests();
private:
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	void handleNewClient(const SOCKET& userSocket);
	std::mutex _usersMu;
};
