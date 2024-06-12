#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handleFactory, LoggedUser* user, RoomManager& roomManager) : 
	m_handleFactory(handleFactory), 
	m_user(user), 
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
		(reqInfo.RequestId == GET_HIGH_SCORE_REQ) ||
		(reqInfo.RequestId == GET_PERSONAL_STATS_REQ) ||
		(reqInfo.RequestId == ADD_QUESTION_REQ);
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
	case ADD_QUESTION_REQ:
		return this->addQuestion(reqInfo);
	}
}

std::vector<std::string> MenuRequestHandler::statsToVector(PlayerResults user_stats)
{
	std::vector<std::string> stats_in_vector;
	stats_in_vector.push_back(std::to_string(user_stats.correctAnswerCount + user_stats.wrongAnswerCount));
	stats_in_vector.push_back(std::to_string(user_stats.correctAnswerCount));
	stats_in_vector.push_back(std::to_string(user_stats.calculateRating()));
	stats_in_vector.push_back(std::to_string(user_stats.averageAnswerTime));
	stats_in_vector.push_back(std::to_string(user_stats.gamesPlayed));
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

void MenuRequestHandler::setUpdateOfUsers(const bool& val)
{
	for (auto it : this->m_handleFactory.GetLoginManager().getUsers())
	{
		it->setUpdateInRooms(val);
	}
}

RequestResult MenuRequestHandler::logOut(RequestInfo& reqInfo)
{
	LoginManager::getInstance(this->m_handleFactory.getDatabase()).logout(m_user->getUsername());
	LogoutResponse logOut_res = { WORKING_STATUS };
	return { JsonResponsePacketSerialize::serializeLogoutResponse(logOut_res), (IRequestHandler*)m_handleFactory.createLoginRequestHandler() };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo& reqInfo)
{

	if (m_user->getUpdateInRooms())
	{
		GetRoomsResponse getRooms_res = { WORKING_STATUS, m_roomManager.getRooms() };
		this->m_user->setUpdateInRooms(false);
		return { JsonResponsePacketSerialize::serializeGetRoomResponse(getRooms_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
	}
	else
	{
		GetRoomsResponse getRooms_res;
		getRooms_res.status = NOT_SOMTHING_TO_UPDATE;
		return { JsonResponsePacketSerialize::serializeGetRoomResponse(getRooms_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
	}
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& reqInfo)
{
	GetPersonalStatsResponse getPersonalStats_res;
	if (!m_handleFactory.getDatabase()->doesUserHaveStats(m_user->getId()))
	{
		getPersonalStats_res = { FAILED_STATUS, PlayerResults() };
		return { JsonResponsePacketSerialize::serializeGetPersonalStatsResponse(getPersonalStats_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
	}

	PlayerResults user_stats = m_handleFactory.getStatisticsManager().getUserStatistics(m_user->getId());
	getPersonalStats_res = { WORKING_STATUS, user_stats };


	return { JsonResponsePacketSerialize::serializeGetPersonalStatsResponse(getPersonalStats_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo& reqInfo)
{
	std::vector<PlayerResults> highScores = m_handleFactory.getStatisticsManager().getHighScore();
	GetHighScoreResponse getHighScore_res = { WORKING_STATUS, highScores};
	return { JsonResponsePacketSerialize::serializeHighScoreResponse(getHighScore_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo& reqInfo)
{
	JoinRoomRequest joinRoom_req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);
	ErrorResponse error_res;
	if (m_roomManager.doesRoomExist(joinRoom_req.roomId))
	{
		// Check if room is full
		if (m_roomManager.getRoom(joinRoom_req.roomId)->getRoomData().maxPlayers == m_roomManager.getRoom(joinRoom_req.roomId)->getAllUsers().size())
		{
			error_res = { "room is full!" };
		}
		else // Join player to room if there's enough space
		{
			m_roomManager.getRoom(joinRoom_req.roomId)->addUser(m_user);
			// updating the users a new user joined
			for (auto it : m_roomManager.getRoom(joinRoom_req.roomId)->getAllLoggedUsers())
			{
				it->setUpdateInOwnRoom(true);
			}
			JoinRoomResponse joinRoom_res = { WORKING_STATUS };
			return { JsonResponsePacketSerialize::serializeJoinRoomResponse(joinRoom_res), (IRequestHandler*)m_handleFactory.createRoomMemberRequestHandler(this->m_user, m_roomManager.getRoom(joinRoom_req.roomId)) };
		}
	}
	error_res = { "Room doesn't exist" };
	return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };

}

RequestResult MenuRequestHandler::createRoom(RequestInfo& reqInfo)
{
	CreateRoomRequest createRoom_req = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);
	int numOfQuestions = (m_handleFactory.getDatabase())->getTotalAmountOfQuestions();
	
	// Check if the new room is valid
	if (createRoom_req.questionCount >= MIN_NUM_OF_QUESTIONS && createRoom_req.questionCount <= numOfQuestions && createRoom_req.answerTimeout >= MIN_ANS_TIME && createRoom_req.maxUsers >= MIN_USERS)
	{
		RoomData newRoomData = { 0, createRoom_req.roomName, createRoom_req.maxUsers, createRoom_req.questionCount, createRoom_req.answerTimeout, ACTIVE_ROOM, false, m_user->getId()};
		int roomId = m_roomManager.createRoom(m_user, newRoomData);
		newRoomData.id = roomId;
		
		CreateRoomResponse createRoom_res = { WORKING_STATUS, roomId };
		return {JsonResponsePacketSerialize::serializeCreateRoomResponse(createRoom_res),  (IRequestHandler*)m_handleFactory.createRoomAdminRequestHandler(this->m_user, this->m_roomManager.getRoom(roomId))};
	}
	ErrorResponse error_res = { "Invalid room settings!" };	
	return { JsonResponsePacketSerialize::serializeErrorResponse(error_res), (IRequestHandler*)m_handleFactory.createMenuRequestHandler(m_user) };
}

RequestResult MenuRequestHandler::addQuestion(RequestInfo& reqInfo)
{
	AddQwestionRequest add_question_res = JsonRequestPacketDeserializer::deserializeAddQuestionReqest(reqInfo.buffer);
	std::string correct_ans = add_question_res.possible_ans[0];
	add_question_res.possible_ans.erase(add_question_res.possible_ans.begin());
	Question question(add_question_res.questionText, add_question_res.possible_ans, correct_ans);
	m_handleFactory.getDatabase()->insertQuestionIntoDB(question);
	
}


