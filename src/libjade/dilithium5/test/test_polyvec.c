#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "notrandombytes.c"
#include "fips202.h"
#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_eta_jazz(polyvecl *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_gamma1_jazz(polyvecl *v, const uint8_t seed[CRHBYTES], uint16_t nonce);
 
void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_reduce_jazz(polyvecl *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_add_jazz(polyvecl *w, polyvecl *u, polyvecl *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_ntt_jazz(polyvecl *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_invntt_tomont_jazz(polyvecl *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_poly_montgomery_jazz(polyvecl *r, poly *a, polyvecl *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_acc_montgomery_jazz(poly *w, polyvecl *u, polyvecl *v);
uint32_t PQCLEAN_DILITHIUM5_CLEAN_polyvecl_chknorm_jazz(polyvecl *v, int32_t B);

void PQCLEAN_DILITHIUM5_CLEAN_polyveck_uniform_eta_jazz(polyveck *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

void PQCLEAN_DILITHIUM5_CLEAN_polyveck_reduce_jazz(polyveck *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyveck_caddq_jazz(polyveck *v);

void PQCLEAN_DILITHIUM5_CLEAN_polyveck_add_jazz(polyveck *w, const polyveck *u, const polyveck *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyveck_sub_jazz(polyveck *w, const polyveck *u, const polyveck *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyveck_shiftl_jazz(polyveck *v);

void PQCLEAN_DILITHIUM5_CLEAN_polyveck_ntt_jazz(polyveck *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyveck_invntt_tomont_jazz(polyveck *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyveck_pointwise_poly_montgomery_jazz(polyveck *r, const poly *a, const polyveck *v);

int PQCLEAN_DILITHIUM5_CLEAN_polyveck_chknorm_jazz(const polyveck *v, int32_t B);

void PQCLEAN_DILITHIUM5_CLEAN_polyveck_power2round_jazz(polyveck *v1, polyveck *v0, const polyveck *v);
void PQCLEAN_DILITHIUM5_CLEAN_polyveck_decompose_jazz(polyveck *v1, polyveck *v0, const polyveck *v);
unsigned int PQCLEAN_DILITHIUM5_CLEAN_polyveck_make_hint_jazz(polyveck *h,
        const polyveck *v0,
        const polyveck *v1);
void PQCLEAN_DILITHIUM5_CLEAN_polyveck_use_hint_jazz(polyveck *w, const polyveck *u, const polyveck *h);

void PQCLEAN_DILITHIUM5_CLEAN_polyveck_pack_w1_jazz(uint8_t r[K * POLYW1_PACKEDBYTES], const polyveck *w1);

void PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_expand_jazz(polyvecl mat[K], const uint8_t rho[SEEDBYTES]);

void PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_pointwise_montgomery_jazz(polyveck *t, const polyvecl mat[K], const polyvecl *v);

int main ()
{
  checkpolyvecluniform(CRHBYTES, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_eta, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_eta_jazz, "polyvecl_uniform_eta");
  checkpolyvecluniform(CRHBYTES, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_gamma1, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_gamma1_jazz, "polyvecl_uniform_gamma1");

  checkpolyvecl(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_reduce, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_reduce_jazz, "polyvecl_reduce");
  checkpolyvecl3(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_add, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_add_jazz, "polyvecl_add");
  checkpolyvecl(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_ntt, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_ntt_jazz, "polyvecl_ntt");
  checkpolyvecl(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_invntt_tomont, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_invntt_tomont_jazz, "polyvecl_invntt_tomont");
  checkpolyvecl_poly(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_poly_montgomery, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_poly_montgomery_jazz, "polyvecl_pointwise_poly_montgomery");
  checkpoly_polyvecl(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_acc_montgomery, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_acc_montgomery_jazz, "polyvecl_pointwise_acc_montgomery");
  checkpolyveclint(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_chknorm, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_chknorm_jazz, "polyvecl_chknorm_jazz");

  checkpolyveckuniform(CRHBYTES, PQCLEAN_DILITHIUM5_CLEAN_polyveck_uniform_eta, PQCLEAN_DILITHIUM5_CLEAN_polyveck_uniform_eta_jazz, "polyveck_uniform_eta");

  checkpolyveck(PQCLEAN_DILITHIUM5_CLEAN_polyveck_reduce, PQCLEAN_DILITHIUM5_CLEAN_polyveck_reduce_jazz, "polyveck_reduce");
  checkpolyveck(PQCLEAN_DILITHIUM5_CLEAN_polyveck_caddq, PQCLEAN_DILITHIUM5_CLEAN_polyveck_caddq_jazz, "polyveck_caddq");

  checkpolyveck3(PQCLEAN_DILITHIUM5_CLEAN_polyveck_add, PQCLEAN_DILITHIUM5_CLEAN_polyveck_add_jazz, "polyveck_add");
  checkpolyveck3(PQCLEAN_DILITHIUM5_CLEAN_polyveck_sub, PQCLEAN_DILITHIUM5_CLEAN_polyveck_sub_jazz, "polyveck_sub");
  checkpolyveck(PQCLEAN_DILITHIUM5_CLEAN_polyveck_shiftl, PQCLEAN_DILITHIUM5_CLEAN_polyveck_shiftl_jazz, "polyveck_shiftl");

  checkpolyveck(PQCLEAN_DILITHIUM5_CLEAN_polyveck_ntt, PQCLEAN_DILITHIUM5_CLEAN_polyveck_ntt_jazz, "polyveck_ntt");
  checkpolyveck(PQCLEAN_DILITHIUM5_CLEAN_polyveck_invntt_tomont, PQCLEAN_DILITHIUM5_CLEAN_polyveck_invntt_tomont_jazz, "polyveck_invntt_tomont");
  checkpolyveck_poly(PQCLEAN_DILITHIUM5_CLEAN_polyveck_pointwise_poly_montgomery, PQCLEAN_DILITHIUM5_CLEAN_polyveck_pointwise_poly_montgomery_jazz, "polyveck_pointwise_poly_montgomery");

  checkpolyveckint(PQCLEAN_DILITHIUM5_CLEAN_polyveck_chknorm, PQCLEAN_DILITHIUM5_CLEAN_polyveck_chknorm_jazz, "polyveck_chknorm_jazz");

  checkpolyveck3(PQCLEAN_DILITHIUM5_CLEAN_polyveck_power2round, PQCLEAN_DILITHIUM5_CLEAN_polyveck_power2round_jazz, "polyveck_power2round");
  checkpolyveck3(PQCLEAN_DILITHIUM5_CLEAN_polyveck_decompose, PQCLEAN_DILITHIUM5_CLEAN_polyveck_decompose_jazz, "polyveck_decompose");
  checkpolyveck3_u32(PQCLEAN_DILITHIUM5_CLEAN_polyveck_make_hint, PQCLEAN_DILITHIUM5_CLEAN_polyveck_make_hint_jazz, "polyveck_make_hint");
  checkpolyveck3(PQCLEAN_DILITHIUM5_CLEAN_polyveck_use_hint, PQCLEAN_DILITHIUM5_CLEAN_polyveck_use_hint_jazz, "polyveck_use_hint");

  checkpolyveckpackw1(PQCLEAN_DILITHIUM5_CLEAN_polyveck_pack_w1, PQCLEAN_DILITHIUM5_CLEAN_polyveck_pack_w1_jazz, "polyveck_pack_w1");

  checkmat(SEEDBYTES, PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_expand, PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_expand_jazz, "polyvec_matrix_expand");

  checkpolyvecl_mat(PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_pointwise_montgomery, PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_pointwise_montgomery_jazz, "polyvec_matrix_pointwise_montgomery");

  return 0;
}

