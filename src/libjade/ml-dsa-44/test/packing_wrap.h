#ifndef JASMIN_MLDSA44_PACKING_WRAP_H
#define JASMIN_MLDSA44_PACKING_WRAP_H

#include "jasmin_params.h"
#include <stdint.h>

void JASMIN_MLDSA44_pack_sk_internal(uint8_t sk[JASMIN_MLDSA44_CRYPTO_SECRETKEYBYTES], const uint8_t* rho_tr_key[3], const int32_t* to_s1_s2[3]);
void JASMIN_MLDSA44_unpack_sk_internal(uint8_t* rho_tr_key[3], int32_t* to_s1_s2[3], const uint8_t sk[JASMIN_MLDSA44_CRYPTO_SECRETKEYBYTES]);

void JASMIN_MLDSA44_pack_sk(uint8_t sk[JASMIN_MLDSA44_CRYPTO_SECRETKEYBYTES], const uint8_t rho[SEEDBYTES], const uint8_t tr[TRBYTES], const uint8_t key[SEEDBYTES], const polyveck *t0, const polyvecl *s1, const polyveck *s2) {
  const uint8_t* rho_tr_key[3];
  rho_tr_key[0] = rho;
  rho_tr_key[1] = tr;
  rho_tr_key[2] = key;

  const int32_t* t0_s1_s2[3];
  t0_s1_s2[0] = (int32_t*) t0;
  t0_s1_s2[1] = (int32_t*) s1;
  t0_s1_s2[2] = (int32_t*) s2;

  JASMIN_MLDSA44_pack_sk_internal(sk, rho_tr_key, t0_s1_s2);
}

void JASMIN_MLDSA44_unpack_sk(uint8_t rho[SEEDBYTES], uint8_t tr[TRBYTES], uint8_t key[SEEDBYTES], polyveck *t0, polyvecl *s1, polyveck *s2,const uint8_t sk[JASMIN_MLDSA44_CRYPTO_SECRETKEYBYTES]) {
  uint8_t* rho_tr_key[3];
  rho_tr_key[0] = rho;
  rho_tr_key[1] = tr;
  rho_tr_key[2] = key;

  int32_t* t0_s1_s2[3];
  t0_s1_s2[0] = (int32_t*) t0;
  t0_s1_s2[1] = (int32_t*) s1;
  t0_s1_s2[2] = (int32_t*) s2;

  JASMIN_MLDSA44_unpack_sk_internal(rho_tr_key, t0_s1_s2, sk);
}

#endif
