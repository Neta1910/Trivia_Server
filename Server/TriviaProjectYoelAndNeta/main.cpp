#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#include <thread>

#define PORT 8826


int main()
{
	try
	{
		Server myServer;

		std::thread connecterThread(&Server::run, &myServer);

		connecterThread.join();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}