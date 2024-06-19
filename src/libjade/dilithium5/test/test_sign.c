#include "notrandombytes.c"

#include "test_macros.h"

#include "sign.h"

#ifndef TESTS
#define TESTS 1000
#endif

void PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed_jazz(uint8_t *pk, uint8_t *sk, uint8_t *sb);

int main ()
{
    check_pksk_pksksb(PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed_jazz, PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed, "crypto_sign_keypair_seed");

    return 0;
}
