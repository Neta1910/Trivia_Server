#pragma once

// ---- Response Codes ----
enum ResponseCodes
{
	CODE_LOGIN_RESP = 200,
	CODE_SIGN_UP_RESP,
	CODE_ERROR_RESPONSE,
	LOGOUT_RESP,
	GET_ROOM_RESP,
	GET_PLAYERS_RESP,
	JOIN_ROOM_RESP,
	CREATE_ROOM_RESP,
	GET_HIGH_SCORE_RESP
};

enum RequestCodes
{
	CODE_LOGIN_REQ = 100,
	CODE_SIGN_UP_REQ,
	CODE_ERROR_REQ,
	LOGOUT_REQ,
	GET_ROOM_REQ,
	GET_PLAYERS_REQ,
	JOIN_ROOM_REQ,
	CREATE_ROOM_REQ,
	GET_HIGH_SCORE_REQ
};

// ---- Message constants ----
#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"

// ---- Error Messages ----
#define INVALID_REQUEST "Invalid Request"

#define ROOM_ID "roomId"

#define ROOM_NAME "roomName"
#define MAX_USERS "maxUsers"
#define QUESTION_COUNT "questionCount"
#define ANSOWER_TIMEOUT "answerTimeout"
