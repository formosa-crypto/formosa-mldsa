#! /usr/bin/env python3

from dilithium import Dilithium3

from Crypto.Hash import SHAKE128
from tqdm import tqdm

KAT_ITERATIONS = 10000


class RNG:
    def __init__(self):
        self.shake = SHAKE128.new()
        self.shake.update(b"")

    def read(self, length):
        return self.shake.read(length)


def generate_hash(algorithm):
    rng = RNG()
    kat_hasher = SHAKE128.new()

    print(
        "ML-DSA-{}{}: Generating SHAKE-128 32-byte hash using {} sets of KATs.".format(
            algorithm.k, algorithm.l, KAT_ITERATIONS
        )
    )

    for i in tqdm(range(KAT_ITERATIONS)):
        zeta = rng.read(32)
        vk, sk = algorithm.keygen(zeta)

        msg_len = 33 * (i + 1)
        msg = rng.read(msg_len)

        signing_randomness = rng.read(32)
        sig = algorithm.sign(sk, msg, signing_randomness)

        kat_hasher.update(vk)
        kat_hasher.update(sk)
        kat_hasher.update(sig)

    print(bytes(kat_hasher.read(32)).hex())


generate_hash(Dilithium3)
