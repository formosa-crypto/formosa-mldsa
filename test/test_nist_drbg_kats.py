from ml_dsa import ML_DSA
import json
import hashlib
from tqdm import tqdm

ml_dsa_65 = ML_DSA('ml_dsa_65_ref')

# ----- NIST KAT Tests -----
with open("nist_drbg_kats/nist_drbg_kats_65.json", "r") as nistkats_65_raw:
    nistkats_65 = json.load(nistkats_65_raw)

    # TODO: Extend to 1000
    for kat in tqdm(nistkats_65[0:500]):
        # Test key generation.
        key_generation_seed = bytearray.fromhex(kat['key_generation_seed'])
        (verification_key, signing_key) = ml_dsa_65.generate_keypair(key_generation_seed)

        sha3_256_hash_of_verification_key = hashlib.sha3_256(verification_key.raw).digest()
        assert sha3_256_hash_of_verification_key == bytes.fromhex((kat['sha3_256_hash_of_verification_key']))

        sha3_256_hash_of_signing_key = hashlib.sha3_256(signing_key.raw).digest()
        assert sha3_256_hash_of_signing_key == bytes.fromhex((kat['sha3_256_hash_of_signing_key']))

        # Then signing.

        # We append [0,0] to signal an empty domain separation context, see
        # the comment in ml_dsa.jazz for as to why this is done here instead
        # of there.
        message = bytearray([0, 0]) + bytearray.fromhex(kat['message'])

        signing_randomness = bytearray.fromhex(kat['signing_randomness'])

        signature, _ = ml_dsa_65.sign(signing_key, message, signing_randomness)

        sha3_256_hash_of_signature = hashlib.sha3_256(signature.raw).digest()
        assert sha3_256_hash_of_signature == bytes.fromhex((kat['sha3_256_hash_of_signature']))

        # And lastly, verification.
        ml_dsa_65.verify(verification_key, message, signature)
