import socket

from flask import Flask
from flask_socketio import SocketIO, emit

import Responses
from getMesseges import *

# configuring the flax server
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

# configuring the socket side
cpp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
cpp_socket.connect(SERVER_DATA)


@socketio.on('login')
def handle_login(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        cpp_socket.sendall(getLoginMessege(requests.LoginRequest(data_dict[USER_NAME], data_dict[PASSWORD])))
        serverMessege = Responses.LoginResponse(get_server_message(cpp_socket))
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
        cpp_socket.sendall(getSignUpMessege(
            requests.SignUpRequest(data_dict[USER_NAME], data_dict[PASSWORD], data_dict[EMAIL], data_dict[ADDRESS],
                                   data_dict[PHONE_NUMBER], data_dict[BIRTH_DATE])))
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
