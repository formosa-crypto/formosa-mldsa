import pytest

from Crypto.Hash import SHAKE128

KATS_TO_ACCUMULATE = 10000


@pytest.fixture()
def expected_final_hash(ml_dsa):
    if ml_dsa.parameter_set == "44":
        return "6a9b0e409516b34c706e2abaae5441b10baae85e98e3fafba5b25d864fe2b0aa"
    elif ml_dsa.parameter_set == "65":
        return "8fc42bd9a915e5d5b5b7be9d1f882034c80c55e1f1b61b37af670635e7db1b64"
    elif ml_dsa.parameter_set == "87":
        return "e7a492c025f68d76d3e7d7a093e367126aa9b1d461bf876385a095f2bec1e431"


def test_accumulated_kats(ml_dsa, expected_final_hash):
    rng = SHAKE128.new()
    rng.update(b"")

    kat_hasher = SHAKE128.new()

    for i in range(KATS_TO_ACCUMULATE):
        key_generation_seed = bytearray(rng.read(32))
        (verification_key, signing_key) = ml_dsa.generate_keypair(key_generation_seed)

        message_size = 33 * (i + 1)
        message = rng.read(message_size)
        message = bytearray([0, 0]) + bytearray(message)

        signing_randomness = bytearray(rng.read(32))
        signature = ml_dsa.sign(signing_key, message, signing_randomness)

        verification_result = ml_dsa.verify(verification_key, message, signature)
        assert verification_result == 0

        kat_hasher.update(verification_key.raw)
        kat_hasher.update(signing_key.raw)
        kat_hasher.update(signature.raw)

    final_hash = bytes(kat_hasher.read(32)).hex()

    assert final_hash == expected_final_hash
