#include "Communicator.h"
#define LENGTH_OF_HELLO 5

Communicator::Communicator(const SOCKET& socket) :
	m_serverSocket(socket)
{
}

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
			{
				throw std::exception(__FUNCTION__);
			}

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
	while (true)
	{
		try
		{

			// Inserting user into the map
			LoginRequestHandler* newHandler = new LoginRequestHandler();
			this->m_usersMu.lock();
			this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(userSocket, newHandler));
			this->m_usersMu.unlock();

			//std::string beginningMessage = "Hello";
			//Helper::sendData(userSocket, beginningMessage);

			std::string clientMessage = Helper::getStringPartFromSocket(userSocket, LENGTH_OF_HELLO);
			std::cout << "Message from client: " << clientMessage << std::endl;
			RequestInfo reqInfo;
			// Convert user message from string to buffer form (vector of bytes)
			reqInfo.buffer = stringToBuffer(clientMessage);
			reqInfo.receivalTime = getCurrentTime();
			if (newHandler->isRequestRelevant(reqInfo))
			{

			}
			else
			{

			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			closesocket(userSocket);
		}
	}
}

std::vector<BYTE> Communicator::stringToBuffer(std::string str)
{
	std::vector<BYTE> data(str.begin(), str.end());
	return data;
}

time_t Communicator::getCurrentTime()
{
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	return end_time;	
}
