#pragma once
#include "pch.h"
#include "json.hpp"
#include "ResponseStructs.h"

using json = nlohmann::json;

class JsonResponsePacketSerialize
{
public:

	static JsonResponsePacketSerialize& getInstance()
	{
		static JsonResponsePacketSerialize instance;
		return instance;
	}

	// Delete copy constructor and assignment operator for singleton
	JsonResponsePacketSerialize(JsonResponsePacketSerialize const&) = delete;
	void operator=(JsonResponsePacketSerialize const&) = delete;

	// v1 Serieleser
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& response);
	static std::vector<unsigned char> serializeSignUpResponse(const SignupResponse& response);
	static std::vector<unsigned char> serializeErrorResponse(const  ErrorResponse& response);

	// v2.0.0 Serieleser
	static std::vector<unsigned char> serializeLogoutResponse(const LogoutResponse& response);
	static std::vector<unsigned char> serializeGetRoomResponse(const GetRoomsResponse& response);
	static std::vector<unsigned char> serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& response);
	static std::vector<unsigned char> serializeJoinRoomResponse(const JoinRoomResponse& response);
	static std::vector<unsigned char> serializeCreateRoomResponse(const CreateRoomResponse& response);
	static std::vector<unsigned char> serializeHighScoreResponse(const GetHighScoreResponse& response);
	static std::vector<unsigned char> serializeGetPersonalStatsResponse(const GetPersonalStatsResponse& response);

	// V3 serializer
	static std::vector<unsigned char> serializeCloseRoomResponse(const CloseRoomResponse& response);
	static std::vector<unsigned char> serializeStartGameResponse(const StartGameResponse& response);
	static std::vector<unsigned char> serializeGetRoomStateResponse(const GetRoomStateResponse& response);
	static std::vector<unsigned char> serializeLeaveRoomResponse(const LeaveRoomResponse& response);
	static std::vector<unsigned char> serializeAmIAdminResponse(const AmIAdminResponse& response);


	// V4 serializer
	static std::vector<unsigned char> serializeLeaveGameResponseResponse(const LeaveGameResponse& response);
	static std::vector<unsigned char> serializeGetQuestionResponseResponse(const GetQuestionResponse& response);
	static std::vector<unsigned char> serializeSubmitAnswerResponseResponse(const SubmitAnswerResponse& response);
	static std::vector<unsigned char> serializeGetGameResultsResponseResponse(const GetGameResultsResponse& response);
	static std::vector<unsigned char> serializeAddQuestionResponse(const addQuestionResponse& response);

	// general functions
	static std::vector<unsigned char> parseDataIntoMessage(json j, const int& respCode );
	static std::vector<unsigned char> turnIntToBytes(const int& num);
	static void padWithZeros(std::vector<unsigned char>* data, const int& amountOfZeroz);
private:
	JsonResponsePacketSerialize() {};
};
