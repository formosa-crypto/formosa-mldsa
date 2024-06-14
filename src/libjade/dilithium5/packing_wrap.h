#ifndef PQCLEAN_DILITHIUM5_CLEAN_PACKING_WRAP_H
#define PQCLEAN_DILITHIUM5_CLEAN_PACKING_WRAP_H
#include "params.h"
#include "packing.h"
#include <stdint.h>

void PQCLEAN_DILITHIUM5_CLEAN_pack_sk_internal_jazz(uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES], const uint8_t* rho_tr_key[3], const int32_t* to_s1_s2[3]);
void PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_internal_jazz(uint8_t* rho_tr_key[3], int32_t* to_s1_s2[3], const uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES]);

void PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz(uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES], const uint8_t rho[SEEDBYTES], const uint8_t tr[SEEDBYTES], const uint8_t key[SEEDBYTES], const polyveck *t0, const polyvecl *s1, const polyveck *s2) {
  const uint8_t* rho_tr_key[3];
  rho_tr_key[0] = rho;
  rho_tr_key[1] = tr;
  rho_tr_key[2] = key;

  const int32_t* t0_s1_s2[3];
  t0_s1_s2[0] = (int32_t*) t0;
  t0_s1_s2[1] = (int32_t*) s1;
  t0_s1_s2[2] = (int32_t*) s2;

  PQCLEAN_DILITHIUM5_CLEAN_pack_sk_internal_jazz(sk, rho_tr_key, t0_s1_s2);
}

void PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_jazz(uint8_t rho[SEEDBYTES], uint8_t tr[SEEDBYTES], uint8_t key[SEEDBYTES], polyveck *t0, polyvecl *s1, polyveck *s2,const uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES]) {
  uint8_t* rho_tr_key[3];
  rho_tr_key[0] = rho;
  rho_tr_key[1] = tr;
  rho_tr_key[2] = key;

  int32_t* t0_s1_s2[3];
  t0_s1_s2[0] = (int32_t*) t0;
  t0_s1_s2[1] = (int32_t*) s1;
  t0_s1_s2[2] = (int32_t*) s2;

  PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_internal_jazz(rho_tr_key, t0_s1_s2, sk); 
}

#endif
