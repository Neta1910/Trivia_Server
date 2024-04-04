import json
import socket
import Responses
import requests

SERVER_DATA = ('127.0.0.1', 8826)

MESSAGE_TO_SERVER = "Hello"
NUM_OF_BYTES = 1024

LOGIN = 100
SIGN_UP = 101

SIZE_OF_LENGTH = 4


def get_server_message(sock):
    server_msg = sock.recv(NUM_OF_BYTES)
    server_msg = server_msg.decode()
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

def 
def check_v103(sock : socket):
    # chekes if user has to be loggdin
    sock.sendall(getLoginMessege(requests.LoginRequest("userNotExsisr", "0584029549")))
    resp = get_server_message(sock)
    if ()


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
