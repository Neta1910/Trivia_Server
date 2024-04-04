#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#include <thread>
#include "pch.h"
#include "JsonResponsePacketSerializer.h"
#define PORT 8826


int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		std::thread connecterThread(&Server::run, &myServer);

		connecterThread.join();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occurred: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}