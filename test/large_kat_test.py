from ml_dsa import ML_DSA
import json
from Crypto.Hash import SHAKE128

ml_dsa_65 = ML_DSA("ml_dsa_65_ref")

KAT_ITERATIONS = 10000


class RNG:
    def __init__(self):
        self.shake = SHAKE128.new()
        self.shake.update(b"")

    def read(self, length):
        return self.shake.read(length)


rng = RNG()
kat_hasher = SHAKE128.new()

for i in range(KAT_ITERATIONS):
    key_generation_seed = bytearray(rng.read(32))
    (verification_key, signing_key) = ml_dsa_65.generate_keypair(key_generation_seed)

    message_size = 33 * (i + 1)
    message = rng.read(message_size)
    message = bytearray([0, 0]) + bytearray(message)

    signing_randomness = bytearray(rng.read(32))
    signature = ml_dsa_65.sign(signing_key, message, signing_randomness)

    verification_result = ml_dsa_65.verify(verification_key, message, signature)
    assert verification_result == 0

    kat_hasher.update(verification_key.raw)
    kat_hasher.update(signing_key.raw)
    kat_hasher.update(signature.raw)

final_hash = bytes(kat_hasher.read(32)).hex()
assert final_hash == "8fc42bd9a915e5d5b5b7be9d1f882034c80c55e1f1b61b37af670635e7db1b64"
