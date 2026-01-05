import pytest

from pathlib import Path
import json
import hashlib
import random


@pytest.fixture()
def kats(ml_dsa):
    kat_file = (
        Path(__file__).parent
        / "nist_drbg"
        / "ml_dsa_{}.json".format(ml_dsa.parameter_set)
    )
    with open(kat_file, "r") as kats_raw:
        return json.load(kats_raw)


def test_against_random_nist_drbg_kat(ml_dsa, kats):
    random_kat_number = random.randint(0, len(kats) - 1)
    kat = kats[random_kat_number]

    # Test key generation.
    key_generation_seed = bytearray.fromhex(kat["key_generation_seed"])
    (verification_key, signing_key) = ml_dsa.generate_keypair(key_generation_seed)

    sha3_256_hash_of_verification_key = hashlib.sha3_256(verification_key).digest()
    assert sha3_256_hash_of_verification_key == bytes.fromhex(
        (kat["sha3_256_hash_of_verification_key"])
    )

    sha3_256_hash_of_signing_key = hashlib.sha3_256(signing_key).digest()
    assert sha3_256_hash_of_signing_key == bytes.fromhex(
        (kat["sha3_256_hash_of_signing_key"])
    )

    # Then signing.
    context = bytearray([])
    message = bytearray.fromhex(kat["message"])

    signing_randomness = bytearray.fromhex(kat["signing_randomness"])

    signature, signing_result = ml_dsa.sign(
        signing_key, context, message, signing_randomness
    )
    assert signing_result == 0

    sha3_256_hash_of_signature = hashlib.sha3_256(signature).digest()
    assert sha3_256_hash_of_signature == bytes.fromhex(
        (kat["sha3_256_hash_of_signature"])
    ), print([hex(b) for b in signature[0:32]])

    # And lastly, verification.
    result = ml_dsa.verify(verification_key, context, message, signature)
    assert result == 0
