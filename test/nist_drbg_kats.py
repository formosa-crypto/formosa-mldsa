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

    _ml_dsa.ml_dsa_65_keygen(verification_key, signing_key, bytearray_to_ctype(randomness))

    return (verification_key, signing_key)

def sign(signing_key, message, randomness):
    signature = ctypes.create_string_buffer(3309)

    signing_attempts = _ml_dsa.ml_dsa_65_sign(signature, signing_key, bytearray_to_ctype(message), len(message), bytearray_to_ctype(randomness))

    assert signing_attempts > 0 and signing_attempts <= 814

    return signature

def verify(verification_key, message, signature):
    verification_result = _ml_dsa.ml_dsa_65_verify(verification_key, bytearray_to_ctype(message), len(message), signature)

    assert verification_result == 0

# ----- NIST KAT Tests -----
with open("test/nist_drbg_kats_65.json", "r") as nistkats_65_raw:
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

        # We append [0,0] to signal an empty domain separation context, see
        # the comment in ml_dsa.jazz for as to why this is done here instead
        # of there.
        message = bytearray([0, 0]) + bytearray.fromhex(nistkat['message'])

        signing_randomness = bytearray.fromhex(nistkat['signing_randomness'])

        signature = sign(signing_key, message, signing_randomness)

        sha3_256_hash_of_signature = hashlib.sha3_256(signature.raw).digest()
        assert sha3_256_hash_of_signature == bytes.fromhex((nistkat['sha3_256_hash_of_signature']))

        # And lastly, verification.
        verify(verification_key, message, signature)
