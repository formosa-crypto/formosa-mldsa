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
void PQCLEAN_DILITHIUM5_CLEAN_unpack_pk_jazz(uint8_t rho[SEEDBYTES], polyveck *t1, const uint8_t pk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_PUBLICKEYBYTES]);
void PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz(uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES], const uint8_t rho[SEEDBYTES], const uint8_t tr[SEEDBYTES], const uint8_t key[SEEDBYTES], const polyveck *t0, const polyvecl *s1, const polyveck *s2);
void PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_jazz(uint8_t rho[SEEDBYTES], uint8_t tr[SEEDBYTES], uint8_t key[SEEDBYTES], polyveck *t0, polyvecl *s1, polyveck *s2,const uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES]);

int main ()
{
    check_pk_rhot1(PQCLEAN_DILITHIUM5_CLEAN_pack_pk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_pk, "_pack_pk_jazz");
    check_rhot1_pk(PQCLEAN_DILITHIUM5_CLEAN_unpack_pk_jazz, PQCLEAN_DILITHIUM5_CLEAN_unpack_pk, "_unpack_pk_jazz");
    check_sk_rhotrkeyt0s1s2(PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_sk, "_pack_sk_jazz");
    check_rhotrkeyt0s1s2_sk(PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_jazz, PQCLEAN_DILITHIUM5_CLEAN_unpack_sk, "_unpack_sk_jazz");

    return 0;
}