import socket

# ---- Port range ----
PORT_MIN = 1024
PORT_MAX = 65535
SERVER_PORT = ('', 64446)

MESSAGE_TO_SERVER = "Hello"
NUM_OF_BYTES = 1024


def get_server_message(sock):
    server_msg = sock.recv(NUM_OF_BYTES)
    server_msg = server_msg.decode()
    # Check if server sent the right message
    if server_msg != MESSAGE_TO_SERVER:
        return True
    else:
        return False


def main():
    # Connect to server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect(SERVER_PORT)
        # Get message from server
        if not get_server_message(sock):
            print("[ERROR] Server sent wrong message!")
        # Send message to server
        sock.sendall(MESSAGE_TO_SERVER.encode())

    except socket.error as exception:
        print("[SOCKET ERROR] " + str(exception))


    sock.close()  # End connection with server

if __name__ == "__main__":
    main()
