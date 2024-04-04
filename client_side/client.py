import json
import socket
import Responses
import requests

SERVER_DATA = ('127.0.0.1', 8826)

MESSAGE_TO_SERVER = "Hello"
NUM_OF_BYTES = 1024

LOGIN = 100
SIGN_UP = 101

CODE_LOGIN_RESP = 200
CODE_SIGN_UP_RESP = 201
CODE_ERROR_RESPONSE = 202

SIZE_OF_LENGTH = 4


def get_server_message(sock):
    server_msg = sock.recv(NUM_OF_BYTES)
    server_msg.decode()
    return server_msg


def getLoginMessege(request: requests.LoginRequest):
    dict = {"username: ": request.userName, "password": request.password}
    # Convert the dictionary to JSON string
    return parseRequestToMessege(dict, LOGIN)


def getSignUpMessege(request: requests.SignUpRequest):
    dict = {"username: ": request.userName, "password": request.password, "email": request.email}
    # Convert the dictionary to JSON string
    return parseRequestToMessege(dict, SIGN_UP)


def parseRequestToMessege(data, code):
    res = convertIntIntoByte(code, 1)
    json_string = json.dumps(data)
    # Convert the JSON string to bytes
    json_bytes = json_string.encode('utf-8')
    res += convertIntIntoByte(len(json_bytes), SIZE_OF_LENGTH)
    res += json_bytes
    return res


def convertIntIntoByte(number, numOfBytes):
    # Convert the integer to a byte array
    byte_array = number.to_bytes(numOfBytes, byteorder='big')

    return byte_array

def signInWithUserDosentExsist(sock : socket):
    # checks if user can sign up with same name
    sock.sendall(getLoginMessege(requests.SignUpRequest("userNotExsisr", "0584029549")))
    resp = get_server_message(sock)
    respMessege = Responses.LoginResponse(resp).status
    if status == 1:
        print("Was able to add user that dosent exiset")

def able_to_sign_up_twice(sock : socket):
    # chekes if user has to be loggdin
    sock.sendall(getSignUpMessege(requests.SignUpRequest("userNotExsisr", "0584029549")))
    resp = get_server_message(sock)

    # chekes if user has to be loggdin
    sock.sendall(getSignUpMessege(requests.SignUpRequest("userNotExsisr", "0584029549")))
    resp = get_server_message(sock)
    respStatus = Responses.SignupResponse(resp).status
    if respStatus == 1:
        print("Was able to sign up twice")

def ableToSignUpIfConnected(sock : socket):
    # logging in
    sock.sendall(getLoginMessege(requests.SignUpRequest("userNotExsisr", "0584029549")))
    resp = get_server_message(sock)

    # signing up
    sock.sendall(getLoginMessege(requests.SignUpRequest("userNotExsisr", "0584029549")))
    resp = get_server_message(sock)
    respStatus = Responses.SignupResponse(resp).status
    if respStatus == 1:
        print("Was able to sign if connected ")

def check_user_names(sock : socket):
    return true


def check_v103(sock : socket):
    

def get_code(resp):
    byte = resp[0]
    return int.from_bytes(byte, byteorder='big')



def main():
    # Connect to server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect(SERVER_DATA)
        # Get message from server
        resp = get_server_message(sock)
        if not resp:
            print("[ERROR] Server sent wrong message!")
        else:  # Send message to server
            print("Server resp: ", resp)
            # sending login messeges
            loginReq = requests.LoginRequest("user1", "1234")
            loginMessege = getLoginMessege(loginReq)
            sock.sendall(loginMessege)
            print("server resp: ", get_server_message(sock))

            # dending signUp messeges
            signUpReq = requests.SignUpRequest("user1", "1234", "user1@gmail.com")
            loginMessege = getSignUpMessege(loginReq)
            sock.sendall(loginMessege)
            print("server resp: ", get_server_message(sock))

            sock.sendall(MESSAGE_TO_SERVER.encode())
            print("Client connected successfully :)")

    except socket.error as exception:
        print("[SOCKET ERROR] " + str(exception))

    sock.close()  # End connection with server


if __name__ == "__main__":
    main()
