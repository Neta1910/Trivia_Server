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
	CODE_SIGN_UP_REQ
};

// ---- Message constants ----
#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"

// ---- Error Messages ----
#define INVALID_REQUEST "Invalid Request"
