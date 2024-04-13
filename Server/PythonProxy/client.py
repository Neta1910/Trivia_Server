import socket

from flask import Flask, request
from flask_socketio import SocketIO, emit

import Responses
import requests
from getMesseges import *

# configuring the flax server
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

user_sockets = {}


@socketio.on('connect')
def handle_connect():
    user_id = request.sid  # Use the session ID as a unique identifier for the user
    cpp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    cpp_socket.connect(SERVER_DATA)
    user_sockets[user_id] = cpp_socket
    print(f"Connected user {user_id}")


@socketio.on('login')
def handle_login(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(requests.LoginRequest(data_dict[USER_NAME], data_dict[PASSWORD]).getMessage())
        serverMessege = Responses.LoginResponse(get_server_message(user_sockets[request.sid]))
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('LoginResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('LoginResponse', {'status': FAILED_STATUS})


@socketio.on('signup')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(
            requests.SignUpRequest(data_dict[USER_NAME], data_dict[PASSWORD], data_dict[EMAIL], data_dict[ADDRESS],
                                   data_dict[PHONE_NUMBER], data_dict[BIRTH_DATE]).getMessage())

        serverMessege = Responses.SignupResponse(get_server_message(user_sockets[request.sid]))
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('SignUpResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('SignUpResponse', {'status': FAILED_STATUS})


@socketio.on('getPlayersInRoom')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(
            requests.GetPlayersInRoomRequest(data_dict[ROOM_ID]).getMessage())

        serverMessege = Responses.GetPlayersInRoomResponse(get_server_message(user_sockets[request.sid]))
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getPlayersInRoomResponse', {'status': WORK_STATUS, 'players': serverMessege.players})
    except Exception as e:
        print(e)
        emit('getPlayersInRoomResponse', {'status': FAILED_STATUS})


@socketio.on('joinRoom')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(
            requests.JoinRoomRequest(data_dict[ROOM_ID]).getMessage())

        serverMessege = Responses.JoinRoomResponse(get_server_message(user_sockets[request.sid]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('joinRoomResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('joinRoomResponse', {'status': FAILED_STATUS})


@socketio.on('createRoom')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(
            requests.CreateRoomRequest(data_dict[ROOM_NAME], data_dict[MAX_USERS], data_dict[QUESTION_COUNT],
                                       data_dict[ANSOWER_TIMEOUT]).getMessage())

        serverMessege = Responses.CreateRoomResponse(get_server_message(user_sockets[request.sid]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('createRoomResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('createRoomResponse', {'status': FAILED_STATUS})


@socketio.on('getHighScore')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(requests.HighScoreRequest().getMessage())

        serverMessege = Responses.GetHighScoreResponse(get_server_message(user_sockets[request.sid]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getHighScoreResponse', {'status': WORK_STATUS, 'statistics': serverMessege.statistics})
    except Exception as e:
        print(e)
        emit('getHighScoreResponse', {'status': FAILED_STATUS})


@socketio.on('logout')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(requests.LogoutRequest().getMessage())

        serverMessege = Responses.LogoutResponse(get_server_message(user_sockets[request.sid]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('logoutResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('logoutResponse', {'status': FAILED_STATUS})


@socketio.on('getRooms')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.sid].sendall(requests.GetRoomRequest().getMessage())

        serverMessege = Responses.GetRoomsResponse(get_server_message(user_sockets[request.sid]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('logoutResponse', {'status': WORK_STATUS, 'rooms': serverMessege.rooms})
    except Exception as e:
        print(e)
        emit('logoutResponse', {'status': FAILED_STATUS})


def main():
    socketio.run(app, debug=True, port=5000)


if __name__ == "__main__":
    main()
