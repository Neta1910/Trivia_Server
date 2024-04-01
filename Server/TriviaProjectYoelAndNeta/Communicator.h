#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "Helper.h"
#include "LoginRequestHandler.h"

class Communicator
{
public:
	Communicator(const SOCKET& socket);
	void startHandleRequests();
private:
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;
	void handleNewClient(const SOCKET& userSocket);
	std::mutex m_usersMu;
};
