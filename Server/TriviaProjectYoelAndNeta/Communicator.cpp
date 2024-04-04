#include "Communicator.h"
#define LENGTH_OF_HELLO 5
#define MESSEGE_LENGT 1024
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

void Communicator::sendData(const SOCKET sc, std::vector<unsigned char>& message, const int& flags)
{
	if (send(sc, this->unsignedToChar(message) , message.size() * sizeof(unsigned char), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}

}

std::vector<unsigned char> Communicator::getDataFromSocket(const SOCKET sc, const int bytesNum, const int& flags)
{

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::vector<unsigned char> recieved = this->charToUnsigned
	delete[] data;
	return received;
}

void Communicator::handleNewClient(const SOCKET& userSocket)
{
	while (true)
	{
		try
		{

			// Inserting user into the map
			LoginRequestHandler* newHandler = new LoginRequestHandler();
			this->m_usersMu.lock();
			this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(userSocket, newHandler));
			this->m_usersMu.unlock();

			std::string clientMessage = (userSocket, LENGTH);
			std::cout << "Message from client: " << clientMessage << std::endl;
			// Construct request
			RequestInfo reqInfo;
			reqInfo.buffer = stringToBuffer(clientMessage);
			reqInfo.receivalTime = getCurrentTime();

			if (newHandler->isRequestRelevant(reqInfo)) // For a valid request, move user to the next state
			{
				newHandler->handleRequest(reqInfo);
			}
			else // Assemble error response
			{
				ErrorResponse err;
				err.message = INVALID_REQUEST;
				std::vector<unsigned char> errorMessage = JsonResponsePacketSerialize::serializeErrorResponse(err);
				Helper::sendData(userSocket, std::string (errorMessage.begin(), errorMessage.end()));
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			closesocket(userSocket);
		}
	}
}

std::vector<unsigned char> Communicator::charToUnsigned(const char* data, const int& length)
{
	std::vector<unsigned char> res;
	for (int i = 0; i < length; i++)
	{
		res.push_back(data[i]);
	}
	return res;
}

char* Communicator::unsignedToChar(const std::vector<unsigned char>& data)
{
	char* res = new char[data.size()];
	for (int i = 0; i < data.size(); i++)
	{
		res[i] = data[i];
	}
	return res;
}


time_t Communicator::getCurrentTime()
{
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	return end_time;	
}

