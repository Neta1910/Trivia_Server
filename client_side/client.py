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

def get_server_message(sock):
    server_msg = sock.recv(NUM_OF_BYTES)
    server_msg.decode()  # This line does nothing, you need to assign the result to a variable
    return server_msg


def getLoginMessege(request: requests.LoginRequest):
    dict = {"username": request.userName, "password": request.password}
    # Convert the dictionary to JSON string
    return parseRequestToMessage(dict, LOGIN)


def getSignUpMessege(request: requests.SignUpRequest):
    dict = {"username": request.userName, "password": request.password, "email": request.email}
    # Convert the dictionary to JSON string
    return parseRequestToMessage(dict_data, SIGN_UP)


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
    sock.sendall(getLoginMessege(requests.LoginRequest("userNotExists", "0584029549")))
    resp = get_server_message(sock)
    respMessage = Responses.LoginResponse(resp).status  # Assuming Responses module has LoginResponse class
    if respMessage == 1:  # status might be undefined, assuming it's respMessage
        print("Was able to add user that doesn't exist")


def able_to_sign_up_twice(sock: socket):
    # checks if user has to be logged in
    sock.sendall(getSignUpMessage(requests.SignUpRequest("userNotExists", "0584029549")))
    resp = get_server_message(sock)

    # checks if user has to be logged in
    sock.sendall(getSignUpMessage(requests.SignUpRequest("userNotExists", "0584029549")))
    resp = get_server_message(sock)
    respStatus = Responses.SignupResponse(resp).status  # Assuming Responses module has SignupResponse class
    if respStatus == 1:
        print("Was able to sign up twice")


def ableToSignUpIfConnected(sock: socket):
    # logging in
    sock.sendall(getLoginMessage(requests.SignUpRequest("userNotExists", "0584029549")))
    resp = get_server_message(sock)

    # signing up
    sock.sendall(getLoginMessage(requests.SignUpRequest("userNotExists", "0584029549")))
    resp = get_server_message(sock)
    respStatus = Responses.SignupResponse(resp).status  # Assuming Responses module has SignupResponse class
    if respStatus == 1:
        print("Was able to sign if connected ")


def check_user_names(sock: socket):
    return True


def check_v103(sock: socket):
    signInWithUserDoesntExist(sock)
    able_to_sign_up_twice(sock)
    ableToSignUpIfConnected(sock)


def get_code(resp):
    byte = resp[0]
    return int.from_bytes(byte, byteorder='big')


def main():
    # Connect to server
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        try:
            sock.connect(SERVER_DATA)
            check_v103(sock)
        except OSError:
            print("Socket not cpnected")


if __name__ == "__main__":
    main()
