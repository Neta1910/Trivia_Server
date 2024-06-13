import random
from socket import socket

from CryptoAlgorithm import CryptoAlgorithm


class OTPCryptoAlgorithm(CryptoAlgorithm):
    large_prime = 17
    generator = 12

    ''' Proces:
    1. Server sends the 
    '''

    def __init__(self, key_from_server, user_socket: socket):
        self.keys = list()
        for key in key_from_server:
            self.private_key = random.randint(1, 1000)
            public_key = (self.generator ** self.private_key) % self.large_prime
            user_socket.sendall(public_key)
            self.keys.append((key ** self.private_key) % self.large_prime)

    #      creating a response key of
    def cipher(self, message):
        encoded = ''.join([chr(ord(a) ^ ord(b)) for a, b in zip(message, self.keys)])
        return encoded

    def decrypt(self, otp, secret):
        """Decrypt secret value.

        Keyword arguments:
        otp -- the one-time pad used when the secret value was encrypted.
        secret -- the value to be decrypted.
        """
        result = ""

        for c in secret.upper():
            if c not in otp:
                continue
            else:
                result += charset[otp.find(c)]

        return result
