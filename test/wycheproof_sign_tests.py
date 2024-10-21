from ml_dsa import ML_DSA
import json
import hashlib
from tqdm import tqdm

ml_dsa_65 = ML_DSA('ml_dsa_65_ref')

with open("wycheproof/mldsa_65_standard_sign_test.json", "r") as wycheproof_sign_65_tests_raw:
    tests = json.load(wycheproof_sign_65_tests_raw)

    signing_seed = bytearray([0] * 32)

    for test_group in tests["testGroups"]:
        signing_key = bytearray.fromhex(test_group['privateKey'])
        if len(signing_key) != ml_dsa_65.signing_key_size:
            # If the signing key size in the KAT does not match the
            # signing key size in our implementation, ensure that the KAT
            # key has a corresponding flag set stating that its length is incorrect.
            #
            # This flag is set on the child 'tests' object.
            assert len(test_group["tests"]) == 1
            assert "IncorrectPrivateKeyLength" in test_group["tests"][0]["flags"]

            continue;
        signing_key = ml_dsa_65.bytearray_to_ctype(signing_key)

        for test in test_group["tests"]:
            if "ctx" in test and test["ctx"] != "":
                # TODO: We skip this since our implementation currently does
                # not validate the context.
                continue

            # We append [0,0] to signal an empty domain separation context, see
            # the comment in ml_dsa.jazz for as to why this is done here instead
            # of there.
            message = bytearray([0, 0]) + bytearray.fromhex(test['msg'])

            signature, _ = ml_dsa_65.sign(signing_key, message, signing_seed)

            if test['result'] == 'valid':
                    actual_decoded = bytearray.fromhex(test['sig'])
                    assert signature.raw == actual_decoded, print("Test case ID: {}.\n First 10 bytes of expected signature: {}.\n First 10 bytes of actual signature: {}".format(test['tcId'], [hex(b) for b in actual_decoded[0:10]], [hex(b) for b in signature.raw[0:10]]))

            # TODO: else, the generated signature is invalid; we can
            # check that our own implementation agrees with this judgement,
            # but in order to do so we'd need the verification key in the
            # wycheproof test file.
