import ctypes

# TODO: Get these parameters directly from the source code.
PARAMETERS = {
    "ml_dsa_65_ref": {
        "verification_key_size": 1952,
        "signing_key_size": 4032,
        "signature_size": 3309,
    },
}

class ML_DSA:
    def __init__(self, parameter_set):
        self.verification_key_size = PARAMETERS[parameter_set]["verification_key_size"]
        self.signing_key_size = PARAMETERS[parameter_set]["signing_key_size"]
        self.signature_size = PARAMETERS[parameter_set]["signature_size"]

        self.ml_dsa = ctypes.PyDLL('../{}.so'.format(parameter_set))

    def bytearray_to_ctype(self, ba):
        char_array = ctypes.c_char * len(ba)
        return char_array.from_buffer(ba)

    def generate_keypair(self, randomness):
        assert len(randomness) == 32

        verification_key = ctypes.create_string_buffer(self.verification_key_size)
        signing_key = ctypes.create_string_buffer(self.signing_key_size)

        self.ml_dsa.ml_dsa_65_keygen(verification_key, signing_key, self.bytearray_to_ctype(randomness))

        return (verification_key, signing_key)

    def sign(self, signing_key, message, randomness):
        assert len(randomness) == 32
        signature = ctypes.create_string_buffer(self.signature_size)

        signing_attempts = self.ml_dsa.ml_dsa_65_sign(signature, signing_key, self.bytearray_to_ctype(message), len(message), self.bytearray_to_ctype(randomness))

        assert signing_attempts > 0 and signing_attempts <= 814

        return (signature, signing_attempts)

    def verify(self, verification_key, message, signature):
        return self.ml_dsa.ml_dsa_65_verify(verification_key, self.bytearray_to_ctype(message), len(message), signature)
