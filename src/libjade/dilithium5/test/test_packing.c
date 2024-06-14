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

#include "packing_wrap.h"

void PQCLEAN_DILITHIUM5_CLEAN_pack_pk_jazz(uint8_t pk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_PUBLICKEYBYTES], const uint8_t rho[SEEDBYTES], const polyveck *t1);
void PQCLEAN_DILITHIUM5_CLEAN_unpack_pk_jazz(uint8_t rho[SEEDBYTES], polyveck *t1, const uint8_t pk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_PUBLICKEYBYTES]);
void PQCLEAN_DILITHIUM5_CLEAN_pack_sig_jazz(uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES], const uint8_t c[SEEDBYTES], const polyvecl *z, const polyveck *h);
int PQCLEAN_DILITHIUM5_CLEAN_unpack_sig_jazz(uint8_t c[SEEDBYTES], polyvecl *z, polyveck *h, const uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES]);

int main ()
{
    check_pk_rhot1(PQCLEAN_DILITHIUM5_CLEAN_pack_pk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_pk, "pack_pk_jazz");
    check_rhot1_pk(PQCLEAN_DILITHIUM5_CLEAN_unpack_pk_jazz, PQCLEAN_DILITHIUM5_CLEAN_unpack_pk, "unpack_pk_jazz");
    check_sk_rhotrkeyt0s1s2(PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_sk, "pack_sk_jazz");
    check_rhotrkeyt0s1s2_sk(PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_jazz, PQCLEAN_DILITHIUM5_CLEAN_unpack_sk, "unpack_sk_jazz");
    check_sig_czh(PQCLEAN_DILITHIUM5_CLEAN_pack_sig_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_sig, "pack_sig_jazz");
    check_czh_sig(PQCLEAN_DILITHIUM5_CLEAN_unpack_sig_jazz, PQCLEAN_DILITHIUM5_CLEAN_unpack_sig, "unpack_sig_jazz");
    return 0;
}
