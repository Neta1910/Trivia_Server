#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include "Helper.h"

#define LENGTH 1024
#define CODE_LENGTH 3
#define FIRST_DIGIT 3
#define LENGTH_OF_LENGTH_OF_NAME 2
#define LENGTH_OF_LENGTH_OF_MESSEGE 5
#define NAME_INDEX 5
#define REG_UPDATE "Just update"

/**
 * Constructor for Server class.
 * Initializes a TCP server socket. If socket creation fails, throws an exception.
 */
Server::Server()
{
	// Create a TCP server socket
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Check for socket creation failure
	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

/**
 * Destructor for Server class.
 * Closes the server socket if it is valid.
 */
Server::~Server()
{
	try
	{
		// Close the server socket
		closesocket(_serverSocket);
	}
	catch (...) {}
}

/**
 * Starts the server to listen on a specified port.
 * Binds the server socket to the given port and starts listening for incoming connections.
 *
 * @param port The port number on which the server will listen.
 */
void Server::serve(int port)
{
	struct sockaddr_in sa = { 0 };

	// Set up the sockaddr_in structure
	sa.sin_port = htons(port); // Set the port to listen on
	sa.sin_family = AF_INET;   // Use IPv4 addresses
	sa.sin_addr.s_addr = INADDR_ANY;    // Listen on all available interfaces

	// Bind the server socket to the specified port
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming connections
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;
}

/**
 * Accepts incoming client connections.
 * Runs an infinite loop that accepts new clients and spawns a thread to handle each client's requests.
 */
void Server::acceptClient()
{
	while (true)
	{
		try
		{
			// Output message indicating waiting for client connections
			std::cout << "Waiting for client connection request" << std::endl;

			// Accept a new client connection
			SOCKET client_socket = accept(_serverSocket, NULL, NULL);
			if (client_socket == INVALID_SOCKET)
				throw std::exception(__FUNCTION__);

			// Output message indicating client acceptance
			std::cout << "Client accepted. Server and client can speak" << std::endl;

			// Create a new thread to handle requests for this client
			std::thread userThread(&Server::handleRequests, this, client_socket);
			userThread.detach(); // Detach the thread
		}
		catch (const std::exception&)
		{
			// Output error message
			std::cerr << "User erupted" << std::endl;
		}
	}
}

/**
 * Handles client requests.
 * Processes incoming messages from the client and performs actions based on the message type.
 *
 * @param userSocket The socket connected to the client.
 */
void Server::handleRequests(const SOCKET& userSocket)
{
	std::string name;
	try
	{
		std::string beginingMessege = 
	}
	catch (const std::exception& e)
	{
		// If an exception occurs, log out the user and close the socket
		if (name != "")
		{
			this->_users.erase(name);
			std::cout << name << " Logged out " << std::endl;
		}
		std::cout << e.what() << std::endl;
		closesocket(userSocket);
	}
}

/**
 * Handles the log-in of a client.
 * Adds the client to the server's list of connected users.
 *
 * @param userSocket The socket connected to the client.
 * @param message The received message containing the client's name.
 * @return The name of the client.
 */
std::string Server::handleLogIn(const SOCKET& userSocket, const std::string& message)
{
	// Extract the client's name from the message
	int length = std::stoi(message.substr(FIRST_DIGIT, LENGTH_OF_LENGTH_OF_NAME));
	std::string name = message.substr(NAME_INDEX, length);

	// Lock the mutex for thread safety and add the client to the list of users
	this->_usersMu.lock();
	this->_users.insert(std::pair<std::string, SOCKET>(name, userSocket));
	std::cout << "ADDED new client " << userSocket << ", " << name << " to clients list" << std::endl;
	this->_usersMu.unlock();

	// Send an update message to the client
	Helper::send_update_message_to_client(userSocket, "", "", Helper::getAllNames(this->_users));

	return name;
}

/**
 * Handles update requests from the client.
 * Processes the client's message and updates the server's state accordingly.
 *
 * @param userSocket The socket connected to the client.
 * @param userName The name of the client sending the update.
 * @param message The received message containing the update details.
 * @return An integer status code (0 for no update, 1 for update processed).
 */
int Server::handleUpdateServer(const SOCKET& userSocket, const std::string& userName, const std::string& message)
{
	// Process the update message
	int length = std::stoi(message.substr(FIRST_DIGIT, LENGTH_OF_LENGTH_OF_NAME));
	if (length == 0)
	{
		// If there's no update, just send an update message to the client
		Helper::send_update_message_to_client(userSocket, "", "", Helper::getAllNames(this->_users));
		return 0;
	}
	else
	{
		// Extract the recipient user and message content
		std::string otherUser = message.substr(NAME_INDEX, length);

		int lenNewMessage = std::stoi(message.substr(FIRST_DIGIT + LENGTH_OF_LENGTH_OF_NAME + length, LENGTH_OF_LENGTH_OF_MESSEGE));
		std::string data = message.substr(FIRST_DIGIT + LENGTH_OF_LENGTH_OF_NAME + length + LENGTH_OF_LENGTH_OF_MESSEGE, lenNewMessage);

		// Prepare the file name for storing the message
		std::string formatMessageForFile = "&MAGSH_MESSAGE&&Author&" + userName + "&DATA&" + data;
		std::string fileName = userName > otherUser ? userName + "&" + otherUser : otherUser + "&" + userName;
		fileName += ".txt";

		// Lock the file for thread safety
		if (this->_filesMutex.find(fileName) != this->_filesMutex.end())
		{
			this->_filesMutex.find(fileName)->second.lock();
		}
		else
		{
			this->_filesMutex.emplace(std::piecewise_construct,
				std::forward_as_tuple(fileName),
				std::forward_as_tuple());
			this->_filesMutex.find(fileName)->second.lock();
		}

		// Open the file for appending the message
		std::fstream chatFile(fileName, std::ios::in | std::ios::out | std::ios::app);
		if (!chatFile.is_open()) {
			throw std::invalid_argument("Invalid file");
		}

		// Read the content of the file
		std::string content((std::istreambuf_iterator<char>(chatFile)), std::istreambuf_iterator<char>());

		// Check if it's just an update or a new message
		if (lenNewMessage == 0)
		{
			// Send the update to the client
			Helper::send_update_message_to_client(userSocket, content, otherUser, Helper::getAllNames(this->_users));
			chatFile.close();
			this->_filesMutex.find(fileName)->second.unlock();
			return 1;
		}

		// Append the new message to the file
		chatFile << formatMessageForFile;
		chatFile.close();
		this->_filesMutex.find(fileName)->second.unlock();

		// Add the message to the list and notify any waiting threads
		this->_messagesMu.lock();
		this->_listOfMessages.push_back(formatMessageForFile);
		this->_messagesMu.unlock();


		// Send the update to the client
		Helper::send_update_message_to_client(userSocket, content, otherUser, Helper::getAllNames(this->_users));
	}
}
