import ctypes
import json
import hashlib
from tqdm import tqdm

_ml_dsa = ctypes.PyDLL('/home/efgh/repos/formosa-mldsa/test/ml_dsa_65_ref.so')

def bytearray_to_ctype(ba):
    char_array = ctypes.c_char * len(ba)
    return char_array.from_buffer(ba)

def generate_keypair(randomness):
    verification_key = ctypes.create_string_buffer(1952)
    signing_key = ctypes.create_string_buffer(4032)

    ret = _ml_dsa.ml_dsa_65_keygen(verification_key, signing_key, bytearray_to_ctype(randomness))
    assert ret == 0

    return (verification_key, signing_key)

def sign(signing_key, message, randomness):
    signature = ctypes.create_string_buffer(3309)
    ret = _ml_dsa.ml_dsa_65_sign(signature, signing_key, bytearray_to_ctype(message), len(message), bytearray_to_ctype(randomness))
    assert ret == 0

    return signature

# ----- NIST KAT Tests -----
with open("test/nistkats_65.json", "r") as nistkats_65_raw:
    nistkats_65 = json.load(nistkats_65_raw)

    for nistkat in tqdm(nistkats_65):
        # Test key generation.
        key_generation_seed = bytearray.fromhex(nistkat['key_generation_seed'])
        (verification_key, signing_key) = generate_keypair(key_generation_seed)

        sha3_256_hash_of_verification_key = hashlib.sha3_256(verification_key.raw).digest()
        assert sha3_256_hash_of_verification_key == bytes.fromhex((nistkat['sha3_256_hash_of_verification_key']))

        sha3_256_hash_of_signing_key = hashlib.sha3_256(signing_key.raw).digest()
        assert sha3_256_hash_of_signing_key == bytes.fromhex((nistkat['sha3_256_hash_of_signing_key']))

        # Then signing.
        signing_randomness = bytearray.fromhex(nistkat['signing_randomness'])
        message = bytearray.fromhex(nistkat['message'])

        signature = sign(signing_key, message, signing_randomness)

        sha3_256_hash_of_signature = hashlib.sha3_256(signature.raw).digest()
        assert sha3_256_hash_of_signature == bytes.fromhex((nistkat['sha3_256_hash_of_signature']))
