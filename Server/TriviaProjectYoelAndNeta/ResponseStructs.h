#pragma once
#include "RoomData.h"
#include <vector>
typedef struct LoginResponse
{
	unsigned int status;
};

typedef struct SignupResponse
{
	unsigned int status;
};

typedef struct ErrorResponse
{
	std::string message;
};
typedef struct LogoutResponse
{
	unsigned int status;
};

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
};

typedef struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};


typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

typedef struct JoinRoomResponse
{
	unsigned int status;
};

typedef struct CreateRoomResponse
{
	unsigned int status;
};