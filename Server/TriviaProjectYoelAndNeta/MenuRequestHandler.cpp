#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId >= LOGOUT_RESP && reqInfo.RequestId <= GET_HIGH_SCORE_RESP);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& reqInfo)
{
	switch (reqInfo.RequestId)
	{
	case LOGOUT_RESP:
		return this->signout(reqInfo);
		break;

	case GET_ROOM_RESP:
		return this->getRooms(reqInfo);
		break;
	
	case GET_PLAYERS_RESP:
		return this->getPlayersInRoom(reqInfo);
		break;

	case GET_HIGH_SCORE_RESP:
		return this->getHighScore(reqInfo);
		break;

	case JOIN_ROOM_RESP:
		return this->joinRoom(reqInfo);
		break;

	case CREATE_ROOM_RESP:
		return this->createRoom(reqInfo);
		break;
	default:
		break;
	}
}

RequestResult MenuRequestHandler::signout(const RequestInfo& request)
{
	LogoutResponse res = { LOGOUT_RESP };
	if (this->m_handleFactory.GetLoginManager().login(req.userName, req.password))
	{
		res.status = WORK_STATUS;
	}
	else
	{
		res.status = FAIL_STATUS;
	}
	return { JsonResponsePacketSerialize::serializeLoginResponse(res), nullptr };
}
