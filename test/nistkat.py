import ctypes
import json
import hashlib

_ml_dsa = ctypes.PyDLL('/home/efgh/repos/formosa-mldsa/test/ml_dsa.so')

def bytearray_to_ctype(ba):
    char_array = ctypes.c_char * len(ba)
    return char_array.from_buffer(ba)

def generate_keypair(randomness):
    verification_key = ctypes.create_string_buffer(1952)
    signing_key = ctypes.create_string_buffer(4032)

    ret = _ml_dsa._jade_sign_dilithium_dilithium3_amd64_ref_keypair_derand(verification_key, signing_key, bytearray_to_ctype(randomness))
    assert ret == 0

    return (verification_key.raw, signing_key.raw)

# ----- NIST KAT Tests -----
with open("nistkats_6_5.json", "r") as nistkats_6_5_raw:
    nistkats_6_5 = json.load(nistkats_6_5_raw)

    for nistkat in nistkats_6_5:
        key_generation_seed = bytearray.fromhex(nistkat['key_generation_seed'])
        (verification_key, signing_key) = generate_keypair(key_generation_seed)

        sha3_256_hash_of_verification_key = hashlib.sha3_256(verification_key).digest()
        assert sha3_256_hash_of_verification_key == bytes.fromhex((nistkat['sha3_256_hash_of_verification_key']))

        sha3_256_hash_of_signing_key = hashlib.sha3_256(signing_key).digest()
        assert sha3_256_hash_of_signing_key == bytes.fromhex((nistkat['sha3_256_hash_of_signing_key']))
