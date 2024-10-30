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

void JASMIN_MLDSA87_polyvecl_uniform_eta(polyvecl *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

void JASMIN_MLDSA87_polyvecl_uniform_gamma1(polyvecl *v, const uint8_t seed[CRHBYTES], uint16_t nonce);
 
void JASMIN_MLDSA87_polyvecl_reduce(polyvecl *v);
void JASMIN_MLDSA87_polyvecl_add(polyvecl *w, polyvecl *u, polyvecl *v);
void JASMIN_MLDSA87_polyvecl_ntt(polyvecl *v);
void JASMIN_MLDSA87_polyvecl_invntt_tomont(polyvecl *v);
void JASMIN_MLDSA87_polyvecl_pointwise_poly_montgomery(polyvecl *r, poly *a, polyvecl *v);
void JASMIN_MLDSA87_polyvecl_pointwise_acc_montgomery(poly *w, polyvecl *u, polyvecl *v);
uint32_t JASMIN_MLDSA87_polyvecl_chknorm(polyvecl *v, int32_t B);

void JASMIN_MLDSA87_polyveck_uniform_eta(polyveck *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

void JASMIN_MLDSA87_polyveck_reduce(polyveck *v);
void JASMIN_MLDSA87_polyveck_caddq(polyveck *v);

void JASMIN_MLDSA87_polyveck_add(polyveck *w, const polyveck *u, const polyveck *v);
void JASMIN_MLDSA87_polyveck_sub(polyveck *w, const polyveck *u, const polyveck *v);
void JASMIN_MLDSA87_polyveck_shiftl(polyveck *v);

void JASMIN_MLDSA87_polyveck_ntt(polyveck *v);
void JASMIN_MLDSA87_polyveck_invntt_tomont(polyveck *v);
void JASMIN_MLDSA87_polyveck_pointwise_poly_montgomery(polyveck *r, const poly *a, const polyveck *v);

int JASMIN_MLDSA87_polyveck_chknorm(const polyveck *v, int32_t B);

void JASMIN_MLDSA87_polyveck_power2round(polyveck *v1, polyveck *v0, const polyveck *v);
void JASMIN_MLDSA87_polyveck_decompose(polyveck *v1, polyveck *v0, const polyveck *v);
unsigned int JASMIN_MLDSA87_polyveck_make_hint(polyveck *h,
        const polyveck *v0,
        const polyveck *v1);
void JASMIN_MLDSA87_polyveck_use_hint(polyveck *w, const polyveck *u, const polyveck *h);

void JASMIN_MLDSA87_polyveck_pack_w1(uint8_t r[K * POLYW1_PACKEDBYTES], const polyveck *w1);

void JASMIN_MLDSA87_polyvec_matrix_expand(polyvecl mat[K], const uint8_t rho[SEEDBYTES]);

void JASMIN_MLDSA87_polyvec_matrix_pointwise_montgomery(polyveck *t, const polyvecl mat[K], const polyvecl *v);

int main ()
{
  checkpolyvecluniform(CRHBYTES, JASMIN_MLDSA87_polyvecl_uniform_eta, JASMIN_MLDSA87_polyvecl_uniform_eta, "polyvecl_uniform_eta");
  checkpolyvecluniform(CRHBYTES, JASMIN_MLDSA87_polyvecl_uniform_gamma1, JASMIN_MLDSA87_polyvecl_uniform_gamma1, "polyvecl_uniform_gamma1");

  checkpolyvecl(JASMIN_MLDSA87_polyvecl_reduce, JASMIN_MLDSA87_polyvecl_reduce, "polyvecl_reduce");
  checkpolyvecl3(JASMIN_MLDSA87_polyvecl_add, JASMIN_MLDSA87_polyvecl_add, "polyvecl_add");
  checkpolyvecl(JASMIN_MLDSA87_polyvecl_ntt, JASMIN_MLDSA87_polyvecl_ntt, "polyvecl_ntt");
  checkpolyvecl(JASMIN_MLDSA87_polyvecl_invntt_tomont, JASMIN_MLDSA87_polyvecl_invntt_tomont, "polyvecl_invntt_tomont");
  checkpolyvecl_poly(JASMIN_MLDSA87_polyvecl_pointwise_poly_montgomery, JASMIN_MLDSA87_polyvecl_pointwise_poly_montgomery, "polyvecl_pointwise_poly_montgomery");
  checkpoly_polyvecl(JASMIN_MLDSA87_polyvecl_pointwise_acc_montgomery, JASMIN_MLDSA87_polyvecl_pointwise_acc_montgomery, "polyvecl_pointwise_acc_montgomery");
  checkpolyveclint(JASMIN_MLDSA87_polyvecl_chknorm, JASMIN_MLDSA87_polyvecl_chknorm, "polyvecl_chknorm");

  checkpolyveckuniform(CRHBYTES, JASMIN_MLDSA87_polyveck_uniform_eta, JASMIN_MLDSA87_polyveck_uniform_eta, "polyveck_uniform_eta");

  checkpolyveck(JASMIN_MLDSA87_polyveck_reduce, JASMIN_MLDSA87_polyveck_reduce, "polyveck_reduce");
  checkpolyveck(JASMIN_MLDSA87_polyveck_caddq, JASMIN_MLDSA87_polyveck_caddq, "polyveck_caddq");

  checkpolyveck3(JASMIN_MLDSA87_polyveck_add, JASMIN_MLDSA87_polyveck_add, "polyveck_add");
  checkpolyveck3(JASMIN_MLDSA87_polyveck_sub, JASMIN_MLDSA87_polyveck_sub, "polyveck_sub");
  checkpolyveck(JASMIN_MLDSA87_polyveck_shiftl, JASMIN_MLDSA87_polyveck_shiftl, "polyveck_shiftl");

  checkpolyveck(JASMIN_MLDSA87_polyveck_ntt, JASMIN_MLDSA87_polyveck_ntt, "polyveck_ntt");
  checkpolyveck(JASMIN_MLDSA87_polyveck_invntt_tomont, JASMIN_MLDSA87_polyveck_invntt_tomont, "polyveck_invntt_tomont");
  checkpolyveck_poly(JASMIN_MLDSA87_polyveck_pointwise_poly_montgomery, JASMIN_MLDSA87_polyveck_pointwise_poly_montgomery, "polyveck_pointwise_poly_montgomery");

  checkpolyveckint(JASMIN_MLDSA87_polyveck_chknorm, JASMIN_MLDSA87_polyveck_chknorm, "polyveck_chknorm");

  checkpolyveck3(JASMIN_MLDSA87_polyveck_power2round, JASMIN_MLDSA87_polyveck_power2round, "polyveck_power2round");
  checkpolyveck3(JASMIN_MLDSA87_polyveck_decompose, JASMIN_MLDSA87_polyveck_decompose, "polyveck_decompose");
  checkpolyveck3_u32(JASMIN_MLDSA87_polyveck_make_hint, JASMIN_MLDSA87_polyveck_make_hint, "polyveck_make_hint");
  checkpolyveck3(JASMIN_MLDSA87_polyveck_use_hint, JASMIN_MLDSA87_polyveck_use_hint, "polyveck_use_hint");

  checkpolyveckpackw1(JASMIN_MLDSA87_polyveck_pack_w1, JASMIN_MLDSA87_polyveck_pack_w1, "polyveck_pack_w1");

  checkmat(SEEDBYTES, JASMIN_MLDSA87_polyvec_matrix_expand, JASMIN_MLDSA87_polyvec_matrix_expand, "polyvec_matrix_expand");

  checkpolyvecl_mat(JASMIN_MLDSA87_polyvec_matrix_pointwise_montgomery, JASMIN_MLDSA87_polyvec_matrix_pointwise_montgomery, "polyvec_matrix_pointwise_montgomery");

  return 0;
}

