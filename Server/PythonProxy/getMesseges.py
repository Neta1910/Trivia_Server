from constents import *
import requests
import json
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


def get_code(resp):
    byte = resp[0]
    return int.from_bytes(byte, byteorder='big')