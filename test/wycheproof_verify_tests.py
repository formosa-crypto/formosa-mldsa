from ml_dsa import ML_DSA
import json
from tqdm import tqdm

ml_dsa_65 = ML_DSA("ml_dsa_65_ref")

with open(
    "wycheproof/mldsa_65_standard_verify_test.json", "r"
) as wycheproof_verify_65_tests_raw:
    tests = json.load(wycheproof_verify_65_tests_raw)

    for test_group in tests["testGroups"]:
        verification_key = bytearray.fromhex(test_group["publicKey"])
        if len(verification_key) != ml_dsa_65.verification_key_size:
            # If the verification key size in the KAT does not match the
            # verification key size in our implementation, ensure that the KAT
            # key has a corresponding flag set staring that its length is incorrect.
            #
            # This flag is set on the child `tests` object.
            assert len(test_group["tests"]) == 1
            assert "IncorrectPublicKeyLength" in test_group["tests"][0]["flags"]
            continue

        verification_key = ml_dsa_65.bytearray_to_ctype(verification_key)

        for test in test_group["tests"]:
            if "InvalidContext" in test["flags"]:
                # TODO: We skip this since our implementation currently does
                # not perform context validation and just assumes the context is
                # part of the message.
                continue

            signature = bytearray.fromhex(test["sig"])
            if len(signature) != ml_dsa_65.signature_size:
                # If the KAT signature size does not match the one in our
                # implementation, ensure that the KAT signature has a corresponding
                # flag set stating that its length is incorrect.
                assert "IncorrectSignatureLength" in test["flags"]
                continue
            signature = ml_dsa_65.bytearray_to_ctype(signature)

            if "ctx" in test:
                ctx = bytearray.fromhex(test["ctx"])
                message = (
                    bytearray([0, len(ctx)]) + ctx + bytearray.fromhex(test["msg"])
                )
            else:
                message = bytearray([0, 0]) + bytearray.fromhex(test["msg"])

            verification_result = ml_dsa_65.verify(verification_key, message, signature)

            if test["result"] == "valid":
                assert verification_result == 0, print(
                    "Test ID is: {}".format(test["tcId"])
                )
            else:
                assert verification_result == -1, print(
                    "Test ID: {}".format(test["tcId"])
                )
