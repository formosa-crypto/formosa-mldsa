import ctypes
from pathlib import Path


class ML_DSA:
    def __init__(self, implementation_type, parameter_set):
        # TODO: Get these parameters directly from the source code.
        if parameter_set == "65":
            self.verification_key_size = 1952
            self.signing_key_size = 4032
            self.signature_size = 3309
        else:
            sys.exit("Parameter set not yet implemented.")

        self.parameter_set = parameter_set

        ml_dsa_so = Path(__file__).parent.parent / "ml_dsa_{}_{}.so".format(
            parameter_set, implementation_type
        )
        self.ml_dsa = ctypes.PyDLL(ml_dsa_so)

    def bytearray_to_ctype(self, ba):
        char_array = ctypes.c_char * len(ba)
        return char_array.from_buffer(ba)

    def generate_keypair(self, randomness):
        assert len(randomness) == 32

        verification_key = ctypes.create_string_buffer(self.verification_key_size)
        signing_key = ctypes.create_string_buffer(self.signing_key_size)

        self.ml_dsa.ml_dsa_65_keygen(
            verification_key, signing_key, self.bytearray_to_ctype(randomness)
        )

        return (verification_key, signing_key)

    def sign(self, signing_key, message, randomness):
        assert len(randomness) == 32
        signature = ctypes.create_string_buffer(self.signature_size)

        self.ml_dsa.ml_dsa_65_sign(
            signature,
            signing_key,
            self.bytearray_to_ctype(message),
            len(message),
            self.bytearray_to_ctype(randomness),
        )

        return signature

    def verify(self, verification_key, message, signature):
        return self.ml_dsa.ml_dsa_65_verify(
            verification_key, self.bytearray_to_ctype(message), len(message), signature
        )
