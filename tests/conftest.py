import pytest

import ml_dsa_wrapper


@pytest.fixture(params=[("ref", "65")], scope="module")
def ml_dsa(request):
    return ml_dsa_wrapper.ML_DSA(request.param[0], request.param[1])
