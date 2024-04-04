#pragma once
#include "IRequestHandler.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <map>

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
