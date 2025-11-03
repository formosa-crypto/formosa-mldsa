import pytest

from pathlib import Path
import json


@pytest.fixture()
def signing_test_groups(ml_dsa):
    kat_file = (
        Path(__file__).parent
        / "wycheproof"
        / "mldsa_{}_standard_sign_test.json".format(ml_dsa.parameter_set)
    )
    with open(kat_file, "r") as tests_raw:
        return json.load(tests_raw)["testGroups"]


@pytest.fixture()
def verification_test_groups(ml_dsa):
    kat_file = (
        Path(__file__).parent
        / "wycheproof"
        / "mldsa_{}_standard_verify_test.json".format(ml_dsa.parameter_set)
    )
    with open(kat_file, "r") as tests_raw:
        return json.load(tests_raw)["testGroups"]


def test_wycheproof_sign(ml_dsa, signing_test_groups):
    signing_seed = bytearray([0] * 32)

    for test_group in signing_test_groups:
        signing_key = bytearray.fromhex(test_group["privateKey"])
        if len(signing_key) != ml_dsa.signing_key_size:
            # If the signing key size in the KAT does not match the
            # signing key size in our implementation, ensure that the KAT
            # key has a corresponding flag set stating that its length is incorrect.
            #
            # This flag is set on the child 'tests' object.
            assert len(test_group["tests"]) == 1
            assert "IncorrectPrivateKeyLength" in test_group["tests"][0]["flags"]

            continue

        for test in test_group["tests"]:
            message = bytearray.fromhex(test["msg"])
            if "ctx" in test:
                context = bytearray.fromhex(test["ctx"])
            else:
                context = bytearray([])

            signature, result = ml_dsa.sign(signing_key, context, message, signing_seed)

            if test["result"] == "valid":
                assert result == 0
                expected_signature = bytearray.fromhex(test["sig"])
                assert signature == expected_signature, print(
                    "Test case ID: {}.".format(test["tcId"])
                )
            elif "InvalidContext" in test["flags"]:
                assert result == -1

def test_wycheproof_verify(ml_dsa, verification_test_groups):
    for test_group in verification_test_groups:
        verification_key = bytearray.fromhex(test_group["publicKey"])
        if len(verification_key) != ml_dsa.verification_key_size:
            # If the verification key size in the KAT does not match the
            # verification key size in our implementation, ensure that the KAT
            # key has a corresponding flag set staring that its length is incorrect.
            #
            # This flag is set on the child `tests` object.
            assert len(test_group["tests"]) == 1
            assert "IncorrectPublicKeyLength" in test_group["tests"][0]["flags"]
            continue

        for test in test_group["tests"]:
            signature = bytearray.fromhex(test["sig"])
            if len(signature) != ml_dsa.signature_size:
                # If the KAT signature size does not match the one in our
                # implementation, ensure that the KAT signature has a corresponding
                # flag set stating that its length is incorrect.
                assert "IncorrectSignatureLength" in test["flags"]
                continue

            message = bytearray.fromhex(test["msg"])
            if "ctx" in test:
                context = bytearray.fromhex(test["ctx"])
            else:
                context = bytearray([])

            verification_result = ml_dsa.verify(
                verification_key, context, message, signature
            )

            if test["result"] == "valid":
                assert verification_result == 0, print(
                    "Test ID is: {}".format(test["tcId"])
                )
            else:
                assert verification_result != 0, print(
                    "Test ID: {}, Commment: {}".format(test["tcId"], test["comment"])
                )
