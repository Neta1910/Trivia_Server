import  json
class ErrorResponse:
    def __init__(self, resp):
        json_data = json.loads(resp)
        self.messege = json_data["messege"]

class LoginResponse:
    def __init__(self, resp):
        length = int.from_bytes(bytes(resp[1 : 4]), byteorder='little')
        json_data = json.loads(resp[5 : 5 + length])
        self.status = json_data["status"]

class SignupResponse:
    def __init__(self, resp):
        length = int.from_bytes(resp[1: 5], byteorder='little')
        json_data = json.loads(resp[5: 5 + length])
        self.status = json_data["status"]