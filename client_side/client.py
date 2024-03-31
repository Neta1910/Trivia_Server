import socket

SERVER_DATA = ('127.0.0.1', 8826)

MESSAGE_TO_SERVER = "Hello"
NUM_OF_BYTES = 1024


def get_server_message(sock):
    server_msg = sock.recv(NUM_OF_BYTES)
    server_msg = server_msg.decode()
    # Check if server sent the right message
    if server_msg != MESSAGE_TO_SERVER:
        return False
    else:  # Return true only is the message from server matches the one sent by client
        return True


def main():
    # Connect to server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect(SERVER_DATA)
        # Get message from server
        if not get_server_message(sock):
            print("[ERROR] Server sent wrong message!")
        else:  # Send message to server
            sock.sendall(MESSAGE_TO_SERVER.encode())

    except socket.error as exception:
        print("[SOCKET ERROR] " + str(exception))

    sock.close()  # End connection with server


if __name__ == "__main__":
    main()
