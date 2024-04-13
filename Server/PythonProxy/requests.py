class LoginRequest:
    def __init__(self, user_name, password):
        self.user_name = user_name
        self.password = password


class SignUpRequest:
    def __init__(self, user_name, password, email, address, phone_number, birth_date):
        self.user_name = user_name
        self.password = password
        self.email = email
        self.address = address
        self.phone_number = phone_number
        self.birth_date = birth_date


class RequestResult:
    def __init__(self, response, new_handler):
        self.response = response  # This will be a list of integers representing bytes
        self.new_handler = new_handler  # This assumes `new_handler` is an instance of another Python class


class RequestInfo:
    def __init__(self, request_id, receival_time, buffer):
        self.request_id = request_id
        self.receival_time = receival_time  # This should be a datetime object
        self.buffer = buffer  # This will be a list of integers representing bytes


class GetPlayersInRoomRequest:
    def __init__(self, room_id):
        self.room_id = room_id


class JoinRoomRequest:
    def __init__(self, room_id):
        self.room_id = room_id


class CreateRoomRequest:
    def __init__(self, room_name, max_users, question_count, answer_timeout):
        self.room_name = room_name
        self.max_users = max_users
        self.question_count = question_count
        self.answer_timeout = answer_timeout
