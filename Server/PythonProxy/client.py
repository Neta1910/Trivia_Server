import socket

from flask import Flask, request
from flask_cors import CORS
from flask_socketio import SocketIO, emit

import Requests
import Responses
from ErrorException import ErrorException
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
        user_sockets[get_user_id()].sendall(Requests.LoginRequest(data_dict[USER_NAME], data_dict[PASSWORD]).getMessage())
        serverMessege = Responses.LoginResponse(get_server_message(user_sockets[get_user_id()]))
        emit('LoginResponse', {'status': serverMessege.status})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('signup')
def handle_signup(data_dict):
    user_sockets[get_user_id()].sendall(
        Requests.SignUpRequest(data_dict[USER_NAME], data_dict[PASSWORD], data_dict[EMAIL], data_dict[ADDRESS],
                               data_dict[PHONE_NUMBER], data_dict[BIRTH_DATE]).getMessage())

    serverMessege = Responses.SignupResponse(get_server_message(user_sockets[get_user_id()]))

    emit('SignUpResponse', {'status': serverMessege.status})


@socketio.on('getPlayersInRoom')
def handle_get_players(data):
    user_sockets[get_user_id()].sendall(
        Requests.GetPlayersInRoomRequest(int(data["roomId"])).getMessage())

    serverMessege = Responses.GetPlayersInRoomResponse(get_server_message(user_sockets[get_user_id()]))
    if serverMessege.status == FAILED_STATUS:
        raise Exception
    else:
        emit('getPlayersInRoomResponse', {'status': WORK_STATUS, 'players': serverMessege.players})
    emit('getPlayersInRoomResponse', {'status': FAILED_STATUS})


@socketio.on('joinRoom')
def handle_join_room(data_dict):
    user_sockets[get_user_id()].sendall(
        Requests.JoinRoomRequest(data_dict[ROOM_ID]).getMessage())

    serverMessege = Responses.JoinRoomResponse(get_server_message(user_sockets[get_user_id()]))
    emit('joinRoomResponse', {'status': serverMessege.status})


@socketio.on('createRoom')
def handle_create_room(data):
    try:
        data_dict = data
        user_sockets[get_user_id()].sendall(
            Requests.CreateRoomRequest(data_dict[ROOM_NAME], int(data_dict[MAX_USERS]), int(data_dict[QUESTION_COUNT]),
                                       int(data_dict[ANSOWER_TIMEOUT])).getMessage())
        serverMessege = Responses.CreateRoomResponse(get_server_message(user_sockets[get_user_id()]))
        room_id = serverMessege.roomId
        emit('createRoomResponse', {'status': serverMessege.status, 'roomId': room_id})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('getHighScore')
def handle_get_high():
    try:
        user_sockets[get_user_id()].sendall(Requests.HighScoreRequest().getMessage())
        serverMessege = Responses.GetHighScoreResponse(get_server_message(user_sockets[get_user_id()]))
        emit('getHighScoreResponse', {'status': serverMessege.status, 'statistics': serverMessege.statistics})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('logout')
def handle_logout():
    try:
        user_sockets[get_user_id()].sendall(Requests.LogoutRequest().getMessage())

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
        user_sockets[get_user_id()].sendall(Requests.GetRoomRequest().getMessage())
        serverMessege = Responses.GetRoomsResponse(get_server_message(user_sockets[get_user_id()]))
        emit('getRoomsResponse', {'status': serverMessege.status, 'rooms': serverMessege.rooms})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('getPersonalStats')
def handle_get_personal_stats():
    try:
        user_sockets[get_user_id()].sendall(Requests.personalStatsRequest().getMessage())
        serverMessege = Responses.GetPersonalStatsResponse(get_server_message(user_sockets[get_user_id()]))
        emit('getPersonalStatsResponse', {'status': serverMessege.status, 'statistics': serverMessege.statistics})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('closeRoom')
def handle_close_room(data):
    try:
        user_sockets[get_user_id()].sendall()
        serverMessege = Responses.CloseRoomResponse(get_server_message(user_sockets[get_user_id()]))
        emit('closeRoomResponse', {'status': serverMessege.status})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('startGame')
def handle_start_game(data):
    try:
        user_sockets[get_user_id()].sendall(Requests.StartRoomRequest().getMessage())
        serverMessege = Responses.StartGameResponse(get_server_message(user_sockets[get_user_id()]))
        emit('startGameResponse', {'status': serverMessege.status})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('getRoomState')
def handle_start_game():
    try:
        user_sockets[get_user_id()].sendall(Requests.GetRoomStateRequest().getMessage())

        serverMessege = Responses.GetRoomStaeResponse(get_server_message(user_sockets[get_user_id()]))
        if serverMessege.status == WORK_STATUS:
            emit('getRoomStateResponse',
                     {'status': serverMessege.status, "hasGameBegun": serverMessege.hasGameBegun, "players": serverMessege.players,
                      "questionCount": serverMessege.questionCount, "answerTimeout": serverMessege.answerTimeout})
        else:
            emit('getRoomStateResponse', {'status': serverMessege.status})
    except ErrorException as e:
        emit("error", {'message': e.message})

@socketio.on('AmIAdmin')
def handle_start_game():
    try:
        user_sockets[get_user_id()].sendall(Requests.AmIAdminRequest().getMessage())
        server_message = Responses.AmIAdminResponse(get_server_message(user_sockets[get_user_id()]))
        emit('amIAdminResponse', {'status': server_message.status, "state": server_message.state})
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('getQuestion')
def handle_start_game():
    try:
        user_sockets[get_user_id()].sendall(Requests.GetQuestionRequest().getMessage())
        server_message = Responses.GetQuestionResponse(get_server_message(user_sockets[get_user_id()]))
        emit('getQuestionResponse', server_message.to_dict())
    except ErrorException as e:
        emit("error", {'message': e.message})


@socketio.on('submitAnswer')
def handle_start_game(data):
    try:
        user_sockets[get_user_id()].sendall(Requests.SubmitAnswerRequest().getMessage(data[ANSWER_ID]))
        server_message = Responses.SubmitAnsResp(get_server_message(user_sockets[get_user_id()]))
        emit('submitAnswerResponse', server_message.to_dict())
    except ErrorException as e:
        emit("error", {'message': e.message})

@socketio.on('getRoomRes')
def handle_start_game():
    try:
        user_sockets[get_user_id()].sendall(Requests.GetGameResRequest().getMessage())
        server_message = Responses.GetGameResResp(get_server_message(user_sockets[get_user_id()]))
        emit('getRoomResResponse', server_message.to_dict())
    except ErrorException as e:
        emit("error", {'message': e.message})

@socketio.on('addQuestion')
def handle_start_game(data):
    try:
        user_sockets[get_user_id()].sendall(Requests.AddQuestionRequest().getMessage(data))
        server_message = Responses.AddQuestionResp(get_server_message(user_sockets[get_user_id()]))
        emit('addQuestionResponse', server_message.to_dict())
    except ErrorException as e:
        emit("error", {'message': e.message})

@socketio.on('addQuestion')
def handle_start_game(data):
    try:
        user_sockets[get_user_id()].sendall(Requests.AddQuestionRequest().getMessage(data))
        server_message = Responses.AddQuestionResp(get_server_message(user_sockets[get_user_id()]))
        emit('addQuestionResponse', server_message.to_dict())
    except ErrorException as e:
        emit("error", {'message': e.message})


def main():
    socketio.run(app, debug=True, port=5000, allow_unsafe_werkzeug=True)


if __name__ == "__main__":
    main()
