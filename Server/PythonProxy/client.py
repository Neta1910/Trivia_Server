import socket

from flask import Flask, request
from flask_cors import CORS
from flask_socketio import SocketIO, emit

import Responses
from getMesseges import *

# configuring the flax server
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
CORS(app)  # Apply CORS to your Flask app with default settings
socketio = SocketIO(app, cors_allowed_origins="*")

user_sockets = {}


def get_user_id():
    return f"{request.remote_addr}, {request.headers.get('User-Agent')}"


@socketio.on('connect')
def handle_connect():
    try:
        if get_user_id() not in user_sockets:
            cpp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            cpp_socket.connect(SERVER_DATA)
            user_sockets[get_user_id()] = cpp_socket
            print(f"Connected user {get_user_id()}")
        else:
            print("User already connected")
    except ConnectionRefusedError:
        print("C++ Server is not active")


@socketio.on('login')
def handle_login(data_dict):
    try:
        user_sockets[get_user_id()].sendall(
            requests.LoginRequest(data_dict[USER_NAME], data_dict[PASSWORD]).getMessage())
        serverMessege = Responses.LoginResponse(get_server_message(user_sockets[get_user_id()]))
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('LoginResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('LoginResponse', {'status': FAILED_STATUS})


@socketio.on('signup')
def handle_signup(data_dict):
    user_sockets[get_user_id()].sendall(
        requests.SignUpRequest(data_dict[USER_NAME], data_dict[PASSWORD], data_dict[EMAIL], data_dict[ADDRESS],
                               data_dict[PHONE_NUMBER], data_dict[BIRTH_DATE]).getMessage())

    serverMessege = Responses.SignupResponse(get_server_message(user_sockets[get_user_id()]))

    emit('SignUpResponse', {'status': serverMessege.status})


@socketio.on('getPlayersInRoom')
def handle_get_players(data):
    serverMessege = getPlayersInRoom(int(data["roomId"]))
    if serverMessege.status == FAILED_STATUS:
        raise Exception
    else:
        emit('getPlayersInRoomResponse', {'status': WORK_STATUS, 'players': serverMessege.players})
    emit('getPlayersInRoomResponse', {'status': FAILED_STATUS})


@socketio.on('joinRoom')
def handle_join_room(data_dict):
    user_sockets[get_user_id()].sendall(
        requests.JoinRoomRequest(data_dict[ROOM_ID]).getMessage())

    serverMessege = Responses.JoinRoomResponse(get_server_message(user_sockets[get_user_id()]))
    emit('joinRoomResponse', {'status': serverMessege.status})


@socketio.on('createRoom')
def handle_create_room(data):
    try:
        data_dict = data
        user_sockets[get_user_id()].sendall(
            requests.CreateRoomRequest(data_dict[ROOM_NAME], int(data_dict[MAX_USERS]), int(data_dict[QUESTION_COUNT]),
                                       int(data_dict[ANSOWER_TIMEOUT])).getMessage())
        serverMessege = Responses.CreateRoomResponse(get_server_message(user_sockets[get_user_id()]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:

            room_id = serverMessege.roomId

            emit('createRoomResponse', {'status': WORK_STATUS, 'roomId': room_id})
    except Exception as e:
        print(e)
        emit('createRoomResponse', {'status': FAILED_STATUS})


@socketio.on('getHighScore')
def handle_get_high():
    try:
        user_sockets[get_user_id()].sendall(requests.HighScoreRequest().getMessage())

        serverMessege = Responses.GetHighScoreResponse(get_server_message(user_sockets[get_user_id()]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getHighScoreResponse', {'status': WORK_STATUS, 'statistics': serverMessege.statistics})
    except Exception as e:
        print(e)
        emit('getHighScoreResponse', {'status': FAILED_STATUS})


@socketio.on('logout')
def handle_logout():
    try:
        user_sockets[get_user_id()].sendall(requests.LogoutRequest().getMessage())

        serverMessege = Responses.LogoutResponse(get_server_message(user_sockets[get_user_id()]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            # closing the socket
            user_sockets[get_user_id()].close()
            user_sockets.pop(get_user_id())
            emit('logoutResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('logoutResponse', {'status': FAILED_STATUS})


@socketio.on('getRooms')
def handle_get_rooms():
    try:
        serverMessege = getRooms()
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getRoomsResponse', {'status': WORK_STATUS, 'rooms': serverMessege.rooms})
    except Exception as e:
        print(e)
        emit('getRoomsResponse', {'status': FAILED_STATUS})


@socketio.on('getPersonalStats')
def handle_get_personal_stats():
    try:
        user_sockets[get_user_id()].sendall(requests.personalStatsRequest().getMessage())

        serverMessege = Responses.GetPersonalStatsResponse(get_server_message(user_sockets[get_user_id()]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getPersonalStatsResponse', {'status': WORK_STATUS, 'statistics': serverMessege.statistics})
    except Exception as e:
        print(e)
        emit('getPersonalStatsResponse', {'status': FAILED_STATUS})


@socketio.on('closeRoom')
def handle_close_room(data):
    try:
        roomId = data.roomId
        user_sockets[get_user_id()].sendall()
        serverMessege = Responses.CloseRoomResponse(get_server_message(user_sockets[get_user_id()]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('closeRoomResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('closeRoomResponse', {'status': FAILED_STATUS})


@socketio.on('startGame')
def handle_start_game(data):
    user_sockets[get_user_id()].sendall(requests.StartRoomRequest().getMessage())

    serverMessege = Responses.StartGameResponse(get_server_message(user_sockets[get_user_id()]))

    emit('startGameResponse', {'status': serverMessege.status})


@socketio.on('getRoomState')
def handle_start_game():
    try:
        user_sockets[get_user_id()].sendall(requests.GetRoomStateRequest().getMessage())

        serverMessege = Responses.GetRoomStaeResponse(get_server_message(user_sockets[get_user_id()]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getRoomStateResponse',
                 {'status': WORK_STATUS, "hasGameBegun": serverMessege.hasGameBegun, "players": serverMessege.players,
                  "questionCount": serverMessege.questionCount, "answerTimeout": serverMessege.answerTimeout})
    except Exception as e:
        print(e)
        emit('getRoomStateResponse', {'status': FAILED_STATUS})


@socketio.on('AmIAdmin')
def handle_start_game():
    try:
        user_sockets[get_user_id()].sendall(requests.AmIAdminRequest().getMessage())

        server_message = Responses.AmIAdminResponse(get_server_message(user_sockets[get_user_id()]))

        if server_message.status == FAILED_STATUS:
            raise Exception
        else:
            emit('amIAdminResponse', {'status': WORK_STATUS, "state": server_message.state})
    except Exception as e:
        print(e)
        emit('amIAdminResponse', {'status': FAILED_STATUS})


@socketio.on('getQuestion')
def handle_start_game():
    user_sockets[get_user_id()].sendall(requests.GetQuestionRequest().getMessage())

    server_message = Responses.GetQuestionResponse(get_server_message(user_sockets[get_user_id()]))

    emit('getQuestionResponse',  server_message.to_dict())


@socketio.on('submitAnswer')
def handle_start_game(data):
    print(data)
    user_sockets[get_user_id()].sendall(requests.SubmitAnswerRequest().getMessage(data[ANSWER_ID]))

    server_message = Responses.SubmitAnsResp(get_server_message(user_sockets[get_user_id()]))
    emit('submitAnswerResponse', server_message.to_dict())


@socketio.on('getRoomRes')
def handle_start_game():
    user_sockets[get_user_id()].sendall(requests.GetGameResRequest().getMessage())

    server_message = parseRequestToMessage(get_server_message(user_sockets[get_user_id()]), GET_ROOM_REQ)

    emit('getRoomResResponse', server_message)


def getPlayersInRoom(roomId):
    user_sockets[get_user_id()].sendall(
        requests.GetPlayersInRoomRequest(roomId).getMessage())

    serverMessege = Responses.GetPlayersInRoomResponse(get_server_message(user_sockets[get_user_id()]))
    return serverMessege


def getRooms():
    user_sockets[get_user_id()].sendall(requests.GetRoomRequest().getMessage())

    return Responses.GetRoomsResponse(get_server_message(user_sockets[get_user_id()]))


def main():
    socketio.run(app, debug=True, port=5000, allow_unsafe_werkzeug=True)


if __name__ == "__main__":
    main()
