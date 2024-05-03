#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handleFactory, std::string username, RoomManager& roomManager) : 
	m_handleFactory(handleFactory), 
	m_user(username), 
	m_roomManager(roomManager)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo& reqInfo)
{
	return (reqInfo.RequestId == LOGOUT_REQ) ||
		(reqInfo.RequestId == GET_ROOM_REQ) ||
		(reqInfo.RequestId == GET_PLAYERS_REQ) ||
		(reqInfo.RequestId == JOIN_ROOM_REQ) ||
		(reqInfo.RequestId == CREATE_ROOM_REQ) ||
		(reqInfo.RequestId == GET_HIGH_SCORE_REQ);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& reqInfo)
{
	switch (reqInfo.RequestId)
	{
	case LOGOUT_REQ:
		return this->logOut(reqInfo);
	case GET_ROOM_REQ:
		return this->getRooms(reqInfo);
	case JOIN_ROOM_REQ:
		return this->joinRoom(reqInfo);
	case CREATE_ROOM_REQ:
		return this->createRoom(reqInfo);
	case GET_HIGH_SCORE_REQ:
		return this->getHighScore(reqInfo);
	case GET_PERSONAL_STATS_REQ:
		return this->getPersonalStats(reqInfo);
	}
}

std::vector<std::string> MenuRequestHandler::statsToVector(userStats user_stats)
{
	std::vector<std::string> stats_in_vector;
	stats_in_vector.push_back(std::to_string(user_stats.total_ans));
	stats_in_vector.push_back(std::to_string(user_stats.right_ans));
	stats_in_vector.push_back(std::to_string(user_stats.highScore));
	stats_in_vector.push_back(std::to_string(user_stats.avg_ans_time));
	stats_in_vector.push_back(std::to_string(user_stats.games_played));
	return stats_in_vector;
}

std::vector<std::string> MenuRequestHandler::highestScoreToVector(std::vector<HighestScore>& highest_scores)
{
	std::vector<std::string> highest_scores_in_vector;
	std::vector<HighestScore>::iterator it;
	for (it = highest_scores.begin(); it != highest_scores.end(); ++it)
	{
		highest_scores_in_vector.push_back(std::to_string((*it).user_id) + (*it).username + std::to_string((*it).newHighScore));
	}
	return highest_scores_in_vector;
}

RequestResult MenuRequestHandler::logOut(RequestInfo& reqInfo)
{
	LoginManager::getInstance(this->m_handleFactory.getDatabase()).logout(m_user.getUsername());
	LogoutResponse logOut_res = { WORKING_STATUS };
	return { JsonResponsePacketSerialize::serializeLogoutResponse(logOut_res), (IRequestHandler*)m_handleFactory.createLoginRequestHandler() };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo& reqInfo)
{
	GetRoomsResponse getRooms_res = { WORKING_STATUS, m_roomManager.getRooms() };
	return { JsonResponsePacketSerialize::serializeGetRoomResponse(getRooms_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& reqInfo)
{
	userStats user_stats = m_handleFactory.getStatisticsManager().getUserStatistics(m_user.getId());
	GetPersonalStatsResponse getPersonalStats_res = { WORKING_STATUS, user_stats};
	return { JsonResponsePacketSerialize::serializeGetPersonalStatsResponse(getPersonalStats_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo& reqInfo)
{
	std::vector<HighestScore> highScores = m_handleFactory.getStatisticsManager().getHighScore();
	GetHighScoreResponse getHighScore_res = { WORKING_STATUS, highScores};
	return { JsonResponsePacketSerialize::serializeHighScoreResponse(getHighScore_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo& reqInfo)
{
	JoinRoomRequest joinRoom_req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);
	ErrorResponse error_res;
	if (m_roomManager.doesRoomExist(joinRoom_req.roomId))
	{
		// Check if room is full
		if (m_roomManager.getRoom(joinRoom_req.roomId).getRoomData().maxPlayers == m_roomManager.getRoom(joinRoom_req.roomId).getAllUsers().size())
		{
			error_res = { "room is full!" };
		}
		else // Join player to room if there's enough space
		{
			m_roomManager.getRoom(joinRoom_req.roomId).addUser(m_user);
			JoinRoomResponse joinRoom_res = { WORKING_STATUS };
			return { JsonResponsePacketSerialize::serializeJoinRoomResponse(joinRoom_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(this->m_user, m_roomManager.getRoom(joinRoom_req.roomId)) };
		}
	}
	error_res = { "Room doesn't exist" };
	return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };

}

RequestResult MenuRequestHandler::createRoom(RequestInfo& reqInfo)
{
	CreateRoomRequest createRoom_req = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);
	int numOfQuestions = (m_handleFactory.getDatabase())->getTotalAmountOfQuestions();
	// Check if the new room is valid
	if (createRoom_req.questionCount >= MIN_NUM_OF_QUESTIONS && createRoom_req.questionCount <= numOfQuestions && createRoom_req.answerTimeout >= MIN_ANS_TIME && createRoom_req.maxUsers >= MIN_USERS)
	{
		RoomData newRoomData = { 0, createRoom_req.roomName, createRoom_req.maxUsers, createRoom_req.questionCount, createRoom_req.answerTimeout, ACTIVE_ROOM };
		int roomId = m_roomManager.createRoom(m_user, newRoomData);
		
		CreateRoomResponse createRoom_res = { WORKING_STATUS, roomId };
		return {JsonResponsePacketSerialize::serializeCreateRoomResponse(createRoom_res),  (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(this->m_user, this->m_roomManager.getRoom(roomId))};
	}
	ErrorResponse error_res = { "Invalid room settings!" };	
	return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user.getUsername()) };
}


