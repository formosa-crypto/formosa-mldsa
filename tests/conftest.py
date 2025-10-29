import pytest

import ml_dsa_wrapper


def pytest_addoption(parser):
    parser.addoption(
        "--parameter-set",
        action="store",
        default="65",
        help="ML-DSA parameter set: 44 or 65 or 87",
        choices=("44", "65", "87"),
    )
    parser.addoption(
        "--architecture",
        action="store",
        default="amd64",
        help="CPU architecture: x86-64 or arm-m4",
        choices=("x86-64", "arm-m4"),
    )
    parser.addoption(
        "--implementation-type",
        action="store",
        default="ref",
        help="Implementation type: ref, lowram (on arm-m4 only), and avx2",
        choices=("ref", "lowram", "avx2"),
    )


@pytest.fixture(scope="session")
def ml_dsa(request):
    architecture = request.config.getoption("--architecture")

    if architecture == "x86-64":
        return ml_dsa_wrapper.ML_DSA_X86_64(
            request.config.getoption("--parameter-set"),
            request.config.getoption("--implementation-type"),
        )
    else:
        return ml_dsa_wrapper.ML_DSA_ARM_M4(
            request.config.getoption("--parameter-set"),
            request.config.getoption("--implementation-type"),
        )


@pytest.fixture(scope="session")
def architecture(request):
    return request.config.getoption("--architecture")
