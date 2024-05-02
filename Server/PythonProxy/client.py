import socket

from flask import Flask, request
from flask_cors import CORS
from flask_socketio import SocketIO, emit, join_room, leave_room

import Responses
from RoomData import RoomData
from getMesseges import *

# configuring the flax server
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
CORS(app)  # Apply CORS to your Flask app with default settings
socketio = SocketIO(app, cors_allowed_origins="*")

user_sockets = {}
rooms = {}


@socketio.on('connect')
def handle_connect():
    try:
        user_id = request.remote_addr  # Use the session ID as a unique identifier for the user
        if user_id not in user_sockets:
            cpp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            cpp_socket.connect(SERVER_DATA)
            user_sockets[user_id] = cpp_socket
            print(f"Connected user {user_id}")
        else:
            print("User already connected")
    except ConnectionRefusedError:
        print("C++ Server is not active")


@socketio.on('login')
def handle_login(data):
    try:
        # TO DO - convort data_dict into a simple dict
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.remote_addr].sendall(
            requests.LoginRequest(data_dict[USER_NAME], data_dict[PASSWORD]).getMessage())
        serverMessege = Responses.LoginResponse(get_server_message(user_sockets[request.remote_addr]))
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
        user_sockets[request.remote_addr].sendall(
            requests.SignUpRequest(data_dict[USER_NAME], data_dict[PASSWORD], data_dict[EMAIL], data_dict[ADDRESS],
                                   data_dict[PHONE_NUMBER], data_dict[BIRTH_DATE]).getMessage())

        serverMessege = Responses.SignupResponse(get_server_message(user_sockets[request.remote_addr]))
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('SignUpResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('SignUpResponse', {'status': FAILED_STATUS})


@socketio.on('getPlayersInRoom')
def handle_get_players(data):
    try:
        json_data = json.loads(data)
        serverMessege = getPlayersInRoom(json_data[ROOM_ID])
        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getPlayersInRoomResponse', {'status': WORK_STATUS, 'players': serverMessege.players})
    except Exception as e:
        print(e)
        emit('getPlayersInRoomResponse', {'status': FAILED_STATUS})


@socketio.on('joinRoom')
def handle_join_room(data):
    try:
        data_dict = json.loads(data)  # Convert JSON string to Python dictionary
        user_sockets[request.remote_addr].sendall(
            requests.JoinRoomRequest(data_dict[ROOM_ID]).getMessage())

        serverMessege = Responses.JoinRoomResponse(get_server_message(user_sockets[request.remote_addr]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            join_room(data_dict[ROOM_ID])
            players = getPlayersInRoom((data_dict[ROOM_ID]))
            emit("getPlayersInRoomResponse", {'status': WORK_STATUS, 'players': players}, room=data_dict[ROOM_ID])
            emit('joinRoomResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('joinRoomResponse', {'status': FAILED_STATUS})


@socketio.on('createRoom')
def handle_create_room(data):
    try:
        data_dict = data
        user_sockets[request.remote_addr].sendall(
            requests.CreateRoomRequest(data_dict[ROOM_NAME], int(data_dict[MAX_USERS]), int(data_dict[QUESTION_COUNT]),
                                       int(data_dict[ANSOWER_TIMEOUT])).getMessage())
        serverMessege = Responses.CreateRoomResponse(get_server_message(user_sockets[request.remote_addr]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            room_id = serverMessege.roomId
            join_room(room_id)
            roomData = RoomData(room_id, data_dict[ROOM_NAME], int(data_dict[MAX_USERS]),
                                int(data_dict[QUESTION_COUNT]), int(data_dict[ANSOWER_TIMEOUT]), True)
            emit('createRoomResponse', {'status': WORK_STATUS})
            emit('roomAdded', {"room": roomData})
    except Exception as e:
        print(e)
        emit('createRoomResponse', {'status': FAILED_STATUS})


@socketio.on('getHighScore')
def handle_get_high():
    try:
        user_sockets[request.remote_addr].sendall(requests.HighScoreRequest().getMessage())

        serverMessege = Responses.GetHighScoreResponse(get_server_message(user_sockets[request.remote_addr]))

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
        user_sockets[request.remote_addr].sendall(requests.LogoutRequest().getMessage())

        serverMessege = Responses.LogoutResponse(get_server_message(user_sockets[request.remote_addr]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            # closing the socket
            user_sockets[request.remote_addr].close()
            user_sockets.pop(request.remote_addr)
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
        user_sockets[request.remote_addr].sendall(requests.personalStatsRequest().getMessage())

        serverMessege = Responses.GetPersonalStatsResponse(get_server_message(user_sockets[request.remote_addr]))

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
        user_sockets[request.remote_addr].sendall(requests.personalStatsRequest().getMessage())
        serverMessege = Responses.CloseRoomResponse(get_server_message(user_sockets[request.remote_addr]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('roomDeleted', {'roomId': roomId})
            emit('closeRoomResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('closeRoomResponse', {'status': FAILED_STATUS})


@socketio.on('startGame')
def handle_start_game():
    try:
        user_sockets[request.remote_addr].sendall(requests.StartRoomRequest.getMessage())

        serverMessege = Responses.StartGameResponse(get_server_message(user_sockets[request.remote_addr]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('startGameResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('startGameResponse', {'status': FAILED_STATUS})


@socketio.on('getRoomState')
def handle_start_game():
    try:
        user_sockets[request.remote_addr].sendall(requests.GetRoomStateRequest().getMessage())

        serverMessege = Responses.GetRoomStaeResponse(get_server_message(user_sockets[request.remote_addr]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit('getRoomStateResponse',
                 {'status': WORK_STATUS, "hasGameBegun": serverMessege.hasGameBegun, "players": serverMessege.players,
                  "questionCount": serverMessege.questionCount, "answerTimeout": serverMessege.answerTimeout})
    except Exception as e:
        print(e)
        emit('getRoomStateResponse', {'status': FAILED_STATUS})


@socketio.on('LeaveRoom')
def handle_start_game(data):
    try:
        roomId = data.roomId
        playersInRoom = getPlayersInRoom(roomId).players

        user_sockets[request.remote_addr].sendall(requests.LeaveRoomRequest().getMessage())

        serverMessege = Responses.LeaveRoomResponse(get_server_message(user_sockets[request.remote_addr]))

        if serverMessege.status == FAILED_STATUS:
            raise Exception
        else:
            emit("getPlayersInRoomResponse", {'status': WORK_STATUS, 'players': playersInRoom}, room=roomId)
            leave_room(roomId)
            emit('leaveRoomResponse',
                 {'status': WORK_STATUS, "hasGameBegun": serverMessege.hasGameBegun, "players": serverMessege.players,
                  "questionCount": serverMessege.questionCount, "answerTimeout": serverMessege.answerTimeout})
    except Exception as e:
        print(e)
        emit('leaveRoomResponse', {'status': FAILED_STATUS})


@socketio.on('AmIAdmin')
def handle_start_game():
    try:
        user_sockets[request.remote_addr].sendall(requests.AmIAdminRequest().getMessage())

        server_message = Responses.AmIAdminResponse(get_server_message(user_sockets[request.remote_addr]))

        if server_message.status == FAILED_STATUS:
            raise Exception
        else:
            emit('amIAdminResponse', {'status': WORK_STATUS, "state": server_message.state})
    except Exception as e:
        print(e)
        emit('amIAdminResponse', {'status': FAILED_STATUS})


@socketio.on('LeaveGame')
def handle_start_game():
    try:
        user_sockets[request.remote_addr].sendall(requests.LeaveRoomRequest().getMessage())

        server_message = Responses.LeaveRoomResponse(get_server_message(user_sockets[request.remote_addr]))

        if server_message.status == FAILED_STATUS:
            raise Exception
        else:
            emit('LeaveGameResponse', {'status': WORK_STATUS})
    except Exception as e:
        print(e)
        emit('LeaveGameResponse', {'status': FAILED_STATUS})

@socketio.on('GetQuestion')
def handle_start_game():
    try:
        user_sockets[request.remote_addr].sendall(requests.GetQuestionRequest().getMessage())

        server_message = Responses.GetQuestionResponse(get_server_message(user_sockets[request.remote_addr]))

        if server_message.status == FAILED_STATUS:
            raise Exception
        else:
            emit('GetQuestionResponse', {'status': WORK_STATUS, 'question': server_message.question, 'answers': server_message.answers})
    except Exception as e:
        print(e)
        emit('GetQuestionResponse', {'status': FAILED_STATUS})

@socketio.on('SubmitAsnwer')
def handle_start_game(data):
    try:
        user_sockets[request.remote_addr].sendall(requests.SubmitAnswerRequest().getMessage(data['answerId']))

        server_message = Responses.SubmitAnswerResponse(get_server_message(user_sockets[request.remote_addr]))

        if server_message.status == FAILED_STATUS:
            raise Exception
        else:
            emit('LeaveGameResponse', {'status': WORK_STATUS, 'correctAnswerId': server_message.correctId})
    except Exception as e:
        print(e)
        emit('LeaveGameResponse', {'status': FAILED_STATUS})

@socketio.on('GetGameResults')
def handle_start_game(data):
    try:
        user_sockets[request.remote_addr].sendall(requests.GetGameResultRequest.getMessage())

        server_message = Responses.GetGameResultsResponse(get_server_message(user_sockets[request.remote_addr]))

        if server_message.status == FAILED_STATUS:
            raise Exception
        else:
            emit('LeaveGameResponse', {'status': WORK_STATUS, 'results': server_message.results})
    except Exception as e:
        print(e)
        emit('LeaveGameResponse', {'status': FAILED_STATUS})


def getPlayersInRoom(roomId):
    user_sockets[request.remote_addr].sendall(
        requests.GetPlayersInRoomRequest(roomId).getMessage())

    serverMessege = Responses.GetPlayersInRoomResponse(get_server_message(user_sockets[request.remote_addr]))
    return serverMessege


def getRooms():
    user_sockets[request.remote_addr].sendall(requests.GetRoomRequest().getMessage())

    return Responses.GetRoomsResponse(get_server_message(user_sockets[request.remote_addr]))


def main():
    socketio.run(app, debug=True, port=5000, allow_unsafe_werkzeug=True)


if __name__ == "__main__":
    main()
