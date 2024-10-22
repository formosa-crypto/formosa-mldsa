#! /usr/bin/env python3

from dilithium import Dilithium3
from aes256_ctr_drbg import AES256_CTR_DRBG

import json
import hashlib
from tqdm import tqdm


def generate_nistkats(algorithm):
    kats_formatted = []
    pre_hashed_kats_formatted = []

    entropy_input = bytes([i for i in range(48)])
    rng = AES256_CTR_DRBG(entropy_input)

    print("Generating KATs for ML-DSA-{}{}.".format(algorithm.k, algorithm.l))

    for i in tqdm(range(1000)):
        seed = rng.random_bytes(48)
        drbg = AES256_CTR_DRBG(seed)

        zeta = drbg.random_bytes(32)
        vk, sk = algorithm.keygen(zeta)

        msg_len = 33 * (i + 1)
        msg = rng.random_bytes(msg_len)

        signing_randomness = drbg.random_bytes(32)
        sig = algorithm.sign(sk, msg, signing_randomness)

        kats_formatted.append(
            {
                "key_generation_seed": bytes(zeta).hex(),
                "sha3_256_hash_of_verification_key": bytes(
                    hashlib.sha3_256(vk).digest()
                ).hex(),
                "sha3_256_hash_of_signing_key": bytes(
                    hashlib.sha3_256(sk).digest()
                ).hex(),
                "message": bytes(msg).hex(),
                "signing_randomness": bytes(signing_randomness).hex(),
                "sha3_256_hash_of_signature": bytes(
                    hashlib.sha3_256(sig).digest()
                ).hex(),
            }
        )
        with open(
            "nist_drbg_kats_{}{}.json".format(algorithm.k, algorithm.l), "w"
        ) as f:
            json.dump(kats_formatted, f, ensure_ascii=False, indent=4)


generate_nistkats(Dilithium3)
