import json

import constents
from getMesseges import get_code
from ErrorException import ErrorException
def parseResponse(resp):
    length = int.from_bytes(resp[1:4], byteorder='little')
    json_data = json.loads(resp[5:5 + length].decode())
    if resp[0] == constents.CODE_ERROR_RESPONSE:
        raise ErrorException(json_data["message"])
    return json_data


class LoginResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class SignupResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class ErrorResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.message = json_data["message"]


class LogoutResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class GetRoomsResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.rooms = json_data["rooms"]


class GetPlayersInRoomResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.players = json_data["players"]


class GetHighScoreResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.statistics = json_data["statistics"]


class GetPersonalStatsResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.statistics = json_data["statistics"]


class JoinRoomResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class CreateRoomResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.roomId = json_data["roomId"]


class CloseRoomResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class StartGameResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class GetRoomStaeResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.hasGameBegun = json_data[constents.HAS_GAME_BEGUN]
        self.players = json_data[constents.PLAYERS]
        self.questionCount = json_data[constents.QUESTION_COUNT]
        self.answerTimeout = json_data[constents.ANSOWER_TIMEOUT]


class LeaveRoomResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class AmIAdminResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.state = json_data["state"]


class GetQuestionResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.question = json_data["question"]
        self.answers = json_data["answers"]

    def to_dict(self):
        return {
            "status": self.status,
            "question": self.question,
            "answers": self.answers
        }


class SubmitAnsResp:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.correctAnswerId = json_data["correctAnswerId"]

    def to_dict(self):
        return {
            "status": self.status,
            "correctAnswerId": self.correctAnswerId
        }
