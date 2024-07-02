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
void PQCLEAN_DILITHIUM5_CLEAN_pack_sig_jazz(uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES], const uint8_t c[CTILDEBYTES], const polyvecl *z, const polyveck *h);
int PQCLEAN_DILITHIUM5_CLEAN_unpack_sig_jazz(uint8_t c[CTILDEBYTES], polyvecl *z, polyveck *h, const uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES]);

void check_unpack_sig() {
  int32_t z[N*L];						 
  int32_t z_jazz[N*L];
  int32_t h[N*K];
  int32_t h_jazz[N*K];
  uint8_t c[CTILDEBYTES];
  uint8_t c_jazz[CTILDEBYTES];
  uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES];
  uint8_t sig_jazz[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES];
  for(int t=0; t<TESTS; t++) {
    fillarrnu8(sig, sig_jazz, PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES);
    int r = PQCLEAN_DILITHIUM5_CLEAN_unpack_sig(c, (polyvecl *)z, (polyveck *)h, sig);
    int r_jazz = PQCLEAN_DILITHIUM5_CLEAN_unpack_sig_jazz(c_jazz, (polyvecl *)z_jazz, (polyveck *)h_jazz, sig_jazz);
    if (r != r_jazz) {
      printf("FAIL: unpack_sig\n");
      exit(1);
    }
    if (r == 0) {
      eqarr(N*L, PRId32, z, z_jazz, "unpack_sig");
      eqarr(N*K, PRId32, h, h_jazz, "unpack_sig");
    }
  }
  printf("PASS: unpack_sig_jazz\n");
}

int main ()
{
     check_pk_rhot1(PQCLEAN_DILITHIUM5_CLEAN_pack_pk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_pk, "pack_pk_jazz");
     check_rhot1_pk(PQCLEAN_DILITHIUM5_CLEAN_unpack_pk_jazz, PQCLEAN_DILITHIUM5_CLEAN_unpack_pk, "unpack_pk_jazz");
     check_sk_rhotrkeyt0s1s2(PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz, PQCLEAN_DILITHIUM5_CLEAN_pack_sk, "pack_sk_jazz");
     check_rhotrkeyt0s1s2_sk(PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_jazz, PQCLEAN_DILITHIUM5_CLEAN_unpack_sk, "unpack_sk_jazz");
     check_unpack_sig();
    return 0;
}
