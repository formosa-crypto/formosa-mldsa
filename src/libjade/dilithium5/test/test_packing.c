#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "packing.h"
#include "notrandombytes.c"
#include "fips202.h"
#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

void PQCLEAN_DILITHIUM5_CLEAN_pack_pk_jazz(uint8_t pk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_PUBLICKEYBYTES], const uint8_t rho[SEEDBYTES], const polyveck *t1);
void PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz(uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES], const uint8_t rho[SEEDBYTES], const uint8_t tr[SEEDBYTES], const uint8_t key[SEEDBYTES], const polyveck *t0, const polyvecl *s1, const polyveck *s2);

int main ()
{
    checkpkrhot1(PQCLEAN_DILITHIUM5_CLEAN_pack_pk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_pk, "_pack_pk_jazz");
    checkskrhotrkeyt0s1s2(PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_sk, "_pack_sk_jazz");
    return 0;
}