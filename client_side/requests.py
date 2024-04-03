class LoginRequest:
    def __init__(self, userName, password):
        self.userName = userName
        self.password = password

class SignUpRequest:
    def __init__(self, userName, password, email):
        self.userName = userName
        self.password = password
        self.email = email