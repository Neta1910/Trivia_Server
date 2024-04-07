#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#include <thread>
#include "SqliteDatabase.h"


#include "JsonResponsePacketSerializer.h"
#define PORT 8826


int main()
{
	try
	{
		WSAInitializer wsaInit;
		SQLiteDatabase* db = new SQLiteDatabase();
		Server myServer (db);
		std::thread connecterThread(&Server::run, &myServer);

		connecterThread.join();
		delete db;
	}
	catch (std::exception& e)
	{
		std::cout << "Error occurred: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}