#pragma once
#include "RoomData.h"
struct LoginResponse
{
	unsigned int status;
} typedef  LoginResponse;

struct SignupResponse
{
	unsigned int status;
} typedef  SignupResponse;

struct ErrorResponse
{
	std::string message;
} typedef ErrorResponse;

struct LogoutResponse
{
	unsigned int status;
} typedef LogoutResponse;

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
} typedef GetRoomsResponse;

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
} typedef GetPlayersInRoomResponse;

struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
} typedef GetHighScoreResponse;


struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
} typedef GetPersonalStatsResponse;

struct JoinRoomResponse
{
	unsigned int status;
} typedef JoinRoomResponse;

struct CreateRoomResponse
{
	unsigned int status;
} typedef CreateRoomResponse;