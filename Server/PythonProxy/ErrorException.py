class ErrorException(Exception):
    """Exception raised for custom errors.

    Attributes:
        message -- explanation of the error
    """

    def __init__(self, message):
        self.message = message
        super().__init__(self.message)