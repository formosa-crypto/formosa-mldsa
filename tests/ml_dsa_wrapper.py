import ctypes
from pathlib import Path


class ML_DSA:
    def __init__(self, parameter_set, architecture, implementation_type):
        # TODO: Get these parameters directly from the source code.
        if parameter_set == "44":
            self.verification_key_size = 1312
            self.signing_key_size = 2560
            self.signature_size = 2420
        elif parameter_set == "65":
            self.verification_key_size = 1952
            self.signing_key_size = 4032
            self.signature_size = 3309
        else:  # parameter_set = 87
            self.verification_key_size = 2592
            self.signing_key_size = 4896
            self.signature_size = 4627

        self.parameter_set = parameter_set

        ml_dsa_so = Path(__file__).parent.parent / "ml_dsa_{}_{}_{}.so".format(
            parameter_set, implementation_type, architecture
        )
        self.ml_dsa = ctypes.PyDLL(ml_dsa_so)

    def bytearray_to_ctype(self, ba):
        char_array = ctypes.c_char * len(ba)
        return char_array.from_buffer(ba)

    def generate_keypair(self, randomness):
        assert len(randomness) == 32

        verification_key = ctypes.create_string_buffer(self.verification_key_size)
        signing_key = ctypes.create_string_buffer(self.signing_key_size)

        if self.parameter_set == "44":
            self.ml_dsa.ml_dsa_44_keygen(
                verification_key, signing_key, self.bytearray_to_ctype(randomness)
            )
        elif self.parameter_set == "65":
            self.ml_dsa.ml_dsa_65_keygen(
                verification_key, signing_key, self.bytearray_to_ctype(randomness)
            )
        else:  # self.parameter_set == "87"
            self.ml_dsa.ml_dsa_87_keygen(
                verification_key, signing_key, self.bytearray_to_ctype(randomness)
            )

        return (verification_key, signing_key)

    def sign(self, signing_key, message, randomness):
        assert len(randomness) == 32
        signature = ctypes.create_string_buffer(self.signature_size)

        if self.parameter_set == "44":
            self.ml_dsa.ml_dsa_44_sign(
                signature,
                signing_key,
                self.bytearray_to_ctype(message),
                len(message),
                self.bytearray_to_ctype(randomness),
            )
        elif self.parameter_set == "65":
            self.ml_dsa.ml_dsa_65_sign(
                signature,
                signing_key,
                self.bytearray_to_ctype(message),
                len(message),
                self.bytearray_to_ctype(randomness),
            )
        else:  # self.parameter_set == "87"
            self.ml_dsa.ml_dsa_87_sign(
                signature,
                signing_key,
                self.bytearray_to_ctype(message),
                len(message),
                self.bytearray_to_ctype(randomness),
            )

        return signature

    def verify(self, verification_key, message, signature):
        if self.parameter_set == "44":
            return self.ml_dsa.ml_dsa_44_verify(
                verification_key,
                self.bytearray_to_ctype(message),
                len(message),
                signature,
            )
        elif self.parameter_set == "65":
            return self.ml_dsa.ml_dsa_65_verify(
                verification_key,
                self.bytearray_to_ctype(message),
                len(message),
                signature,
            )
        else:  # self.parameter_set == "87"
            return self.ml_dsa.ml_dsa_87_verify(
                verification_key,
                self.bytearray_to_ctype(message),
                len(message),
                signature,
            )
