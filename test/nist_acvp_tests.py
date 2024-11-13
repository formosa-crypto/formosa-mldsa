from ml_dsa import ML_DSA
import json

ml_dsa_65 = ML_DSA("ml_dsa_65_ref")


def find_expected_result(results, test_id):
    for result in results:
        if result["tcId"] == test_id:
            return result


# Test Keygen.
with open("acvp-1_1_0_36/keygen/prompt.json", "r") as tests_raw, open(
    "acvp-1_1_0_36/keygen/expectedResults.json", "r"
) as expected_results_raw:
    tests = json.load(tests_raw)
    expected_results = json.load(expected_results_raw)

    assert tests["revision"] == "FIPS204"

    for test_group in tests["testGroups"]:
        if test_group["parameterSet"] != "ML-DSA-65":
            continue

        test_group_id = test_group["tgId"]
        for test in test_group["tests"]:
            test_id = test["tcId"]
            key_generation_seed = bytearray.fromhex(test["seed"])
            (verification_key, signing_key) = ml_dsa_65.generate_keypair(
                key_generation_seed
            )

            expected_result = find_expected_result(
                expected_results["testGroups"][test_group_id - 1]["tests"], test_id
            )
            expected_verification_key = bytearray.fromhex(expected_result["pk"])
            expected_signing_key = bytearray.fromhex(expected_result["sk"])

            assert verification_key == expected_verification_key
            assert signing_key == expected_signing_key

# Test Signing.
with open("acvp-1_1_0_36/siggen/prompt.json", "r") as tests_raw, open(
    "acvp-1_1_0_36/siggen/expectedResults.json", "r"
) as expected_results_raw:
    tests = json.load(tests_raw)
    expected_results = json.load(expected_results_raw)

    assert tests["revision"] == "FIPS204"

    for test_group in tests["testGroups"]:
        if test_group["parameterSet"] != "ML-DSA-65":
            continue

        test_group_id = test_group["tgId"]

        for test in test_group["tests"]:
            test_id = test["tcId"]

            signing_key = bytearray.fromhex(test["sk"])
            signing_key = ml_dsa_65.bytearray_to_ctype(signing_key)

            message = bytearray.fromhex(test["message"])

            if test_group["deterministic"]:
                signing_randomness = bytearray([0] * 32)
            else:
                signing_randomness = bytearray.fromhex(test["rnd"])

            signature = ml_dsa_65.sign(signing_key, message, signing_randomness)

            expected_result = find_expected_result(
                expected_results["testGroups"][test_group_id - 1]["tests"], test_id
            )
            expected_signature = bytearray.fromhex(expected_result["signature"])

            assert signature == expected_signature, print(
                "Testcase ID: {}".format(test_id)
            )

# Finally, test verification.
with open("acvp-1_1_0_36/sigver/prompt.json", "r") as tests_raw, open(
    "acvp-1_1_0_36/sigver/expectedResults.json", "r"
) as expected_results_raw:
    tests = json.load(tests_raw)
    expected_results = json.load(expected_results_raw)

    assert tests["revision"] == "FIPS204"

    for test_group in tests["testGroups"]:
        if test_group["parameterSet"] != "ML-DSA-65":
            continue

        test_group_id = test_group["tgId"]
        verification_key = bytearray.fromhex(test_group["pk"])
        verification_key = ml_dsa_65.bytearray_to_ctype(verification_key)

        for test in test_group["tests"]:
            test_id = test["tcId"]

            message = bytearray.fromhex(test["message"])

            signature = bytearray.fromhex(test["signature"])
            signature = ml_dsa_65.bytearray_to_ctype(signature)

            verification_result = ml_dsa_65.verify(verification_key, message, signature)

            expected_result = find_expected_result(
                expected_results["testGroups"][test_group_id - 1]["tests"], test_id
            )

            if expected_result["testPassed"]:
                assert verification_result == 0, print(
                    "Testcase ID: {}".format(test_id)
                )
            else:
                assert verification_result == -1, print(
                    "Testcase ID: {}".format(test_id)
                )
