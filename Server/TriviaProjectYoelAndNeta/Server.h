#pragma once
#include "pch.h"
#include <mutex>
#include <condition_variable>
#include "WSAInitializer.h"
#include "Server.h"
#include <deque>
#include <map>


#define PORT 8826


class Server
{
public:
	Server();
	~Server();
	void serve(int port);
	void run();
	void clear();

private:
	std::map<std::string, SOCKET> _users;
	std::deque<std::string> _listOfMessages;
	SOCKET _serverSocket;
	std::mutex _usersMu;
	std::mutex _messagesMu;
	std::map<std::string, std::mutex> _filesMutex;
	std::condition_variable _condForSendingMessage;
};

