import ctypes
from pathlib import Path

from abc import ABC, abstractmethod

import subprocess


class ML_DSA(ABC):
    @abstractmethod
    def generate_keypair(self, randomness):
        pass

    @abstractmethod
    def sign(self, signing_key, context, message, randomness):
        pass

    @abstractmethod
    def verify(self, verification_key, context, message, signature):
        pass


class ML_DSA_X86_64(ML_DSA):
    def __init__(self, parameter_set, implementation_type):
        ml_dsa_so_name = "ml_dsa_{}_{}_x86-64.so".format(
            parameter_set,
            implementation_type,
        )
        ml_dsa = ctypes.PyDLL(Path(__file__).parent.parent / ml_dsa_so_name)

        self.parameter_set = parameter_set

        # While we could get this parameters from the source code, they
        # change so infrequently that we might as well just hardcode them
        # and be done with it.
        if parameter_set == "44":
            self.verification_key_size = 1312
            self.signing_key_size = 2560
            self.signature_size = 2420

            self.keygen_internal = ml_dsa.ml_dsa_44_keygen
            self.sign_internal = ml_dsa.ml_dsa_44_sign
            self.verify_internal = ml_dsa.ml_dsa_44_verify
        elif parameter_set == "65":
            self.verification_key_size = 1952
            self.signing_key_size = 4032
            self.signature_size = 3309

            self.keygen_internal = ml_dsa.ml_dsa_65_keygen
            self.sign_internal = ml_dsa.ml_dsa_65_sign
            self.verify_internal = ml_dsa.ml_dsa_65_verify
        else:  # parameter_set = 87
            self.verification_key_size = 2592
            self.signing_key_size = 4896
            self.signature_size = 4627

            self.keygen_internal = ml_dsa.ml_dsa_87_keygen
            self.sign_internal = ml_dsa.ml_dsa_87_sign
            self.verify_internal = ml_dsa.ml_dsa_87_verify

    def bytearray_to_ctype(self, ba):
        char_array = ctypes.c_char * len(ba)
        return char_array.from_buffer(ba)

    def bytearray_to_ctype_copy(self, ba):
        char_array = ctypes.c_char * len(ba)
        return char_array.from_buffer_copy(ba)

    def generate_keypair(self, randomness):
        verification_key = ctypes.create_string_buffer(
            b"255", self.verification_key_size
        )
        signing_key = ctypes.create_string_buffer(b"255", self.signing_key_size)

        self.keygen_internal(
            verification_key, signing_key, self.bytearray_to_ctype(randomness)
        )

        return (verification_key.raw, signing_key.raw)

    def sign(self, signing_key, context, message, randomness):
        signature = ctypes.create_string_buffer(b"255", self.signature_size)

        # TODO: Handle this in the Jasmin code.
        message = bytearray([0, len(context)]) + context + message
        self.sign_internal(
            signature,
            self.bytearray_to_ctype_copy(signing_key),
            self.bytearray_to_ctype(message),
            len(message),
            self.bytearray_to_ctype(randomness),
        )

        return signature.raw

    def verify(self, verification_key, context, message, signature):
        # TODO: Handle this in the Jasmin code.
        message = bytearray([0, len(context)]) + context + message
        return self.verify_internal(
            self.bytearray_to_ctype_copy(verification_key),
            self.bytearray_to_ctype(message),
            len(message),
            self.bytearray_to_ctype_copy(signature),
        )


class ML_DSA_ARM_M4(ML_DSA):
    def __init__(self, parameter_set, implementation_type):
        self.parameter_set = parameter_set
        self.wrapper_name = "./ml_dsa_{}_{}_arm-m4.o".format(
            parameter_set, implementation_type
        )

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

    def generate_keypair(self, randomness):
        output = subprocess.check_output(
            [self.wrapper_name, "0"], input=randomness, text=False
        )

        verification_key = output[0 : self.verification_key_size]
        signing_key = output[self.verification_key_size :]

        return (verification_key, signing_key)

    def sign(self, signing_key, context, message, randomness):
        input_bytes = (
            len(context).to_bytes(1, byteorder="little")
            + context
            + len(message).to_bytes(4, byteorder="little")
            + message
            + randomness
            + signing_key
        )

        output = subprocess.check_output(
            [self.wrapper_name, "1"], input=input_bytes, text=False
        )

        return output

    def verify(self, verification_key, context, message, signature):
        input_bytes = (
            len(context).to_bytes(1, byteorder="little")
            + context
            + len(message).to_bytes(4, byteorder="little")
            + message
            + signature
            + verification_key
        )
        output = subprocess.check_output(
            [self.wrapper_name, "2"], input=input_bytes, text=False
        )
        return int.from_bytes(output)
