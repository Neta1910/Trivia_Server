#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <deque>
#include <string>
#include <mutex>
#include <condition_variable>


class Server
{
public:
	Server();
	~Server();
	void serve(int port);
	void acceptClient();
	void handleRequests(const SOCKET& userSocket);
	std::string handleLogIn(const SOCKET& userSocket, const std::string& message);
	int handleUpdateServer(const SOCKET& userSocket, const std::string& name, const std::string& message);

private:
	std::map<std::string, SOCKET> _users;
	std::deque<std::string> _listOfMessages;
	SOCKET _serverSocket;
	std::mutex _usersMu;
	std::mutex _messagesMu;
	std::map<std::string, std::mutex> _filesMutex;
	std::condition_variable _condForSendingMessage;
};

