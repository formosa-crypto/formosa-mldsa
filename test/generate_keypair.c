#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>

#include "api.h"
#include "randombytes.h"

int main(void)
{
    int r;
    uint8_t verification_key[VERIFICATION_KEY_BYTES];
    uint8_t signing_key[SIGNING_KEY_BYTES];
    uint8_t coins[RANDOMNESS_BYTES] = {0};

    r = GENERATE_KEYPAIR_DERAND(verification_key, signing_key, coins);
    assert(r == 0);

    return 0;
}
