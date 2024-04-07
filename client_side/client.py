import json
import socket

import Responses  # Assuming this is a custom module containing response classes
import requests  # Assuming this is a custom module containing request classes

SERVER_DATA = ('127.0.0.1', 8826)

START_MESSEGE = "HELLO"
NUM_OF_BYTES = 1024

LOGIN = 100
SIGN_UP = 101

CODE_LOGIN_RESP = 200
CODE_SIGN_UP_RESP = 201
CODE_ERROR_RESPONSE = 202

SIZE_OF_LENGTH = 4

FAILED_STATUS = 0
WORK_STATUS = 1


def get_server_message(sock):
    server_msg = sock.recv(NUM_OF_BYTES)
    return server_msg


def getLoginMessege(request: requests.LoginRequest):
    dict = {"username": request.userName, "password": request.password}
    # Convert the dictionary to JSON string
    return parseRequestToMessage(dict, LOGIN)


def getSignUpMessege(request: requests.SignUpRequest):
    dict = {"username": request.userName, "password": request.password, "email": request.email}
    # Convert the dictionary to JSON string
    return parseRequestToMessage(dict, SIGN_UP)


def parseRequestToMessage(data, code):
    res = convertIntIntoByte(code, 1)
    json_string = json.dumps(data)
    # Convert the JSON string to bytes
    json_bytes = json_string.encode('utf-8')
    res += convertIntIntoByte(len(json_bytes), SIZE_OF_LENGTH)
    res += json_bytes
    return res


def convertIntIntoByte(number, num_of_bytes):
    # Convert the integer to a byte array
    byte_array = number.to_bytes(num_of_bytes, byteorder='big')

    return byte_array


def signInWithUserDoesntExist(sock: socket):
    # checks if user can sign up with the same name
    sock.sendall(getLoginMessege(requests.LoginRequest("user", "0584029549")))
    resp = get_server_message(sock)
    respMessage = Responses.LoginResponse(resp).status  # Assuming Responses module has LoginResponse class
    if respMessage != FAILED_STATUS:  # status might be undefined, assuming it's respMessage
        print("Was able to add user that doesn't exist")
        return False
    return True


def able_to_sign_up_twice(sock: socket) -> bool:
    # checks if user has to be logged in
    sock.sendall(getSignUpMessege(requests.SignUpRequest("userNotExists", "0584029549", "email")))
    resp = get_server_message(sock)

    # checks if user has to be logged in
    sock.sendall(getSignUpMessege(requests.SignUpRequest("userNotExists", "0584029549", "email")))
    resp = get_server_message(sock)
    respStatus = Responses.SignupResponse(resp).status  # Assuming Responses module has SignupResponse class
    if respStatus != FAILED_STATUS:
        print("Was able to sign up twice")
        return False
    return True


def ableToSignUpIfConnected(sock: socket) -> bool:
    # logging in
    sock.sendall(getSignUpMessege(requests.SignUpRequest("userNotExists", "0584029549", "email")))
    resp = get_server_message(sock)

    # signing up
    sock.sendall(getSignUpMessege(requests.SignUpRequest("userNotExists", "0584029549", "email")))
    resp = get_server_message(sock)
    respStatus = Responses.SignupResponse(resp).status  # Assuming Responses module has SignupResponse class
    if respStatus != FAILED_STATUS:
        print("Was able to sign if connected ")
        return False

    return True


def check_user_names(sock: socket):
    return True


def check_v103(sock: socket):
    if (able_to_sign_up_twice(sock) and signInWithUserDoesntExist(sock)  and ableToSignUpIfConnected(sock)) and check_user_names(sock):
        print("passed tests")
    else:
        print("Error")


def get_code(resp):
    byte = resp[0]
    return int.from_bytes(byte, byteorder='big')


def main():
    # Connect to server
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(SERVER_DATA)
        check_v103(sock)


if __name__ == "__main__":
    main()
