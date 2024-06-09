#pragma once
#include "RoomData.h"
#include <vector>
#include "StatisticsManager.h"
#include "HighestScore.h"
#include "PlayerResults.h"
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
	unsigned int status;
	std::vector<std::string> players;
};

typedef struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<PlayerResults> statistics;
};


typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	PlayerResults statistics;
};

typedef struct JoinRoomResponse
{
	unsigned int status;
};

typedef struct CreateRoomResponse
{
	unsigned int status;
	unsigned int roomId;
};

// ---------------- V3 ---------------------------
typedef struct CloseRoomResponse
{
	unsigned int status;
};

typedef struct StartGameResponse
{
	unsigned int status;
};

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	float answerTimeout;
};

typedef struct LeaveRoomResponse
{
	unsigned int status;
};

// ---------------- V4 ---------------------------

typedef struct AmIAdminResponse
{
	unsigned int status;
	bool state;
};

typedef struct LeaveGameResponse
{
	unsigned int status;
};

typedef struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string> answers;
};

typedef struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
	float avg_time;
};

typedef struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
};

