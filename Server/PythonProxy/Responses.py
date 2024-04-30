import json


def parseResponse(resp):
    length = int.from_bytes(resp[1:4], byteorder='little')
    json_data = json.loads(resp[5:5 + length].decode())
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
        self.hasGameBegun = json_data["hasGameBegun"]
        self.players = json_data["players"]
        self.questionCount = json_data["questionCount"]
        self.answerTimeout = json_data["answerTimeout"]


class LeaveRoomResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class AmIAdminResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.state = json_data["state"]


class LeaveGameResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]


class GetQuestionResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.question = json_data["question"]
        self.answers = json_data["answers"]


class SubmitAnswerResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.correctId = json_data["correctAnswerId"]


class GetGameResultsResponse:
    def __init__(self, resp):
        json_data = parseResponse(resp)
        self.status = json_data["status"]
        self.results = json_data["results"]

