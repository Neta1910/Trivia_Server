#include "Communicator.h"

void Communicator::startHandleRequests()
{
	while (true)
	{
		try
		{
			// Output message indicating waiting for client connections
			std::cout << "Waiting for client connection request" << std::endl;

			// Accept a new client connection
			SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
			if (client_socket == INVALID_SOCKET)
				throw std::exception(__FUNCTION__);

			// Output message indicating client acceptance
			std::cout << "Client accepted. Server and client can speak" << std::endl;

			// Create a new thread to handle requests for this client
			std::thread userThread(&Communicator::handleNewClient, this, client_socket);
			userThread.detach(); // Detach the thread
		}
		catch (const std::exception&)
		{
			// Output error message
			std::cerr << "User erupted" << std::endl;
		}
	}
}

void Communicator::handleNewClient(const SOCKET& userSocket)
{
	std::string name;
	try
	{
		
		std::string beginningMessage = "hello";
		Helper::sendData(userSocket, beginningMessage);

		std::string clientMessage = Helper::getStringPartFromSocket(userSocket, NAME_INDEX);
		std::cout << "Message from client: " << clientMessage << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		closesocket(userSocket);
	}
}
