import  json
class ErrorResponse:
    def __init__(self, resp):
        json_data = json.loads(resp)
        self.messege = json_data["messege"]

class LoginResponse:
    def __init__(self, resp):
        json_data = json.loads(resp)
        self.status = json_data["status"]

class SignupResponse:
    def __init__(self, status):
        json_data = json.loads(resp)
        self.status = json_data["status"]