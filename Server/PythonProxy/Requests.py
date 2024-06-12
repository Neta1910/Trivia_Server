import constents
from getMesseges import *


class LoginRequest:
    def __init__(self, user_name, password):
        self.user_name = user_name
        self.password = password

    def getMessage(self):
        data = {"username": self.user_name, "password": self.password}
        return parseRequestToMessage(data, CODE_LOGIN_REQ)


class SignUpRequest:
    def __init__(self, user_name, password, email, address, phone_number, birth_date):
        self.user_name = user_name
        self.password = password
        self.email = email
        self.address = address
        self.phone_number = phone_number
        self.birth_date = birth_date

    def getMessage(self):
        data = {
            "username": self.user_name,
            "password": self.password,
            "email": self.email,
            "address": self.address,
            "phone_number": self.phone_number,
            "birth_date": self.birth_date
        }
        return parseRequestToMessage(data, CODE_SIGN_UP_REQ)


# Similar implementation for the other classes
class GetPlayersInRoomRequest:
    def __init__(self, room_id):
        self.room_id = room_id

    def getMessage(self):
        data = {"roomId": self.room_id}
        return parseRequestToMessage(data, GET_PLAYERS_REQ)


class JoinRoomRequest:
    def __init__(self, room_id):
        self.room_id = room_id

    def getMessage(self):
        data = {"roomId": self.room_id}
        return parseRequestToMessage(data, JOIN_ROOM_REQ)


class CreateRoomRequest:
    def __init__(self, room_name, max_users, question_count, answer_timeout):
        self.room_name = room_name
        self.max_users = max_users
        self.question_count = question_count
        self.answer_timeout = answer_timeout

    def getMessage(self):
        data = {
            constents.ROOM_NAME: self.room_name,
            constents.MAX_USERS: self.max_users,
            constents.QUESTION_COUNT: self.question_count,
            constents.ANSOWER_TIMEOUT: self.answer_timeout
        }
        return parseRequestToMessage(data, CREATE_ROOM_REQ)


class HighScoreRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_HIGH_SCORE_REQ)


class personalStatsRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_PERSONAL_STATS_REQ)


class LogoutRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, LOGOUT_REQ)


class GetRoomRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_ROOM_REQ)


class StartRoomRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, START_GAME_REQ)


class GetRoomStateRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_ROOM_STATE_REQ)


class LeaveRoomRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, LEAVE_ROOM_REQ)


class AmIAdminRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, AM_I_ADMIN_REQ)


class GetQuestionRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_QUESTION_REQ)


class SubmitAnswerRequest:
    def getMessage(self, submitedAnswerId):
        data = {ANSWER_ID: submitedAnswerId}
        return parseRequestToMessage(data, SUBMIT_ANSWER_REQ)


class GetGameResRequest:
    def getMessage(self):
        data = {}
        return parseRequestToMessage(data, GET_GAME_RESULT_REQ)

class AddQuestionRequest:
    def getMessage(self, data):
        return parseRequestToMessage(data, ADD_QUESTION_REQ)


