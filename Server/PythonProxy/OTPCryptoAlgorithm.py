from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.backends import default_backend

# Generate DH parameters
parameters = dh.generate_parameters(generator=2, key_size=2048, backend=default_backend())

# Generate private keys
private_key_alice = parameters.generate_private_key()
public_key_alice = private_key_alice.public_key()

private_key_bob = parameters.generate_private_key()
public_key_bob = private_key_bob.public_key()

# Serialize public keys (exchange)
public_key_alice_bytes = public_key_alice.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

public_key_bob_bytes = public_key_bob.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

# Deserialize public keys
public_key_alice_received = serialization.load_pem_public_key(
    public_key_alice_bytes,
    backend=default_backend()
)

public_key_bob_received = serialization.load_pem_public_key(
    public_key_bob_bytes,
    backend=default_backend()
)

# Derive the shared secret
shared_secret_alice = private_key_alice.exchange(public_key_bob_received)
shared_secret_bob = private_key_bob.exchange(public_key_alice_received)

# Ensure both shared secrets are equal
assert shared_secret_alice == shared_secret_bob

# Convert shared secret to key (shorten for OTP if necessary)
key = shared_secret_alice[:32]  # Use first 32 bytes for the OTP key

# OTP Encryption and Decryption functions
def otp_encrypt(message, key):
    encrypted_message = bytes([m ^ k for m, k in zip(message, key)])
    return encrypted_message

def otp_decrypt(encrypted_message, key):
    decrypted_message = bytes([c ^ k for c, k in zip(encrypted_message, key)])
    return decrypted_message

# Example usage
message = b"Hello, this is a secret message!"
encrypted_message = otp_encrypt(message, key)
decrypted_message = otp_decrypt(encrypted_message, key)

print("Original message:", message)
print("Encrypted message:", encrypted_message)
print("Decrypted message:", decrypted_message)
