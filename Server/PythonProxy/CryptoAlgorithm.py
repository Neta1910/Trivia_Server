from abc import ABC, abstractmethod


class CryptoAlgorithm(ABC):
    @abstractmethod
    def encrypt(self, message: str) -> str:
        pass

    @abstractmethod
    def decrypt(self, message: str) -> str:
        pass
