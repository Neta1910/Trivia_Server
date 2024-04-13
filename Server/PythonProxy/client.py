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
            emit('LoginResponse', {'data': 'user logged'})
    except Exception as e:
        print(e)
        emit('LoginResponse', {'data': 'user name and password do not match'})


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
            emit('SignUpResponse', {'data': 'user logged'})
    except Exception as e:
        print(e)
        emit('SignUpResponse', {'data': 'user already exists'})


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
            emit('LoginResponse', {'data': 'user logged'})
    except Exception as e:
        print(e)
        emit('LoginResponse', {'data': 'user already exists'})


@socketio.on('signup')
def handle_signup(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        cpp_socket.sendall(
            requests.SignUpRequest(data_dict[USER_NAME], data_dict[PASSWORD], data_dict[EMAIL], data_dict[ADDRESS],
                                   data_dict[PHONE_NUMBER], data_dict[BIRTH_DATE]).getMessage())

        serverMessege = Responses.SignupResponse(get_server_message(cpp_socket))
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('LoginResponse', {'data': 'user logged'})
    except Exception as e:
        print(e)
        emit('LoginResponse', {'data': 'user already exists'})


def main():
    socketio.run(app, debug=True, port=5000)


if __name__ == "__main__":
    main()
