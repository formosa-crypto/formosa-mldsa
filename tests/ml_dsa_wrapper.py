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

    def prepare_context_and_message_for_api(self, context, message):
        uint8_t_ptr = ctypes.POINTER(ctypes.c_uint8)

        context_buffer = self.bytearray_to_ctype(context)
        context_buffer_ptr = ctypes.cast(context_buffer, uint8_t_ptr)
        context_len = len(context)

        message_buffer = self.bytearray_to_ctype(message)
        message_buffer_ptr = ctypes.cast(message_buffer, uint8_t_ptr)
        message_len = len(message)

        context_message_pointers = (uint8_t_ptr * 2)(
            context_buffer_ptr, message_buffer_ptr
        )
        context_message_sizes = (ctypes.c_size_t * 2)(context_len, message_len)

        return context_message_pointers, context_message_sizes

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

        context_message_pointers, context_message_sizes = (
            self.prepare_context_and_message_for_api(context, message)
        )

        result = self.sign_internal(
            signature,
            self.bytearray_to_ctype_copy(signing_key),
            context_message_pointers,
            context_message_sizes,
            self.bytearray_to_ctype(randomness),
        )

        return signature.raw, result

    def verify(self, verification_key, context, message, signature):
        context_message_pointers, context_message_sizes = (
            self.prepare_context_and_message_for_api(context, message)
        )

        return self.verify_internal(
            self.bytearray_to_ctype_copy(verification_key),
            context_message_pointers,
            context_message_sizes,
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
            len(context).to_bytes(4, byteorder="little")
            + context
            + len(message).to_bytes(4, byteorder="little")
            + message
            + randomness
            + signing_key
        )

        result = subprocess.run(
            [self.wrapper_name, "1"], input=input_bytes, capture_output=True, text=False
        )

        if result.returncode == 0:
            returncode = 0
        elif result.returncode == 255:
            returncode = -1
        else:  # shouldn't be possible
            assert False

        return result.stdout, returncode

    def verify(self, verification_key, context, message, signature):
        input_bytes = (
            len(context).to_bytes(4, byteorder="little")
            + context
            + len(message).to_bytes(4, byteorder="little")
            + message
            + signature
            + verification_key
        )

        result = subprocess.run(
            [self.wrapper_name, "2"],
            input=input_bytes,
        )

        if result.returncode == 0:
            returncode = 0
        elif result.returncode == 255:
            returncode = -1
        else:  # shouldn't be possible
            assert False

        return returncode
