#include "version.h"

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

void JASMIN_VERSION(polyvecl_uniform_eta)(polyvecl *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

void JASMIN_VERSION(polyvecl_uniform_gamma1)(polyvecl *v, const uint8_t seed[CRHBYTES], uint16_t nonce);
 
void JASMIN_VERSION(polyvecl_reduce)(polyvecl *v);
void JASMIN_VERSION(polyvecl_add)(polyvecl *w, polyvecl *u, polyvecl *v);
void JASMIN_VERSION(polyvecl_ntt)(polyvecl *v);
void JASMIN_VERSION(polyvecl_invntt_tomont)(polyvecl *v);
void JASMIN_VERSION(polyvecl_pointwise_poly_montgomery)(polyvecl *r, poly *a, polyvecl *v);
void JASMIN_VERSION(polyvecl_pointwise_acc_montgomery)(poly *w, polyvecl *u, polyvecl *v);
uint32_t JASMIN_VERSION(polyvecl_chknorm)(polyvecl *v, int32_t B);

void JASMIN_VERSION(polyveck_uniform_eta)(polyveck *v, const uint8_t seed[CRHBYTES], uint16_t nonce);

void JASMIN_VERSION(polyveck_reduce)(polyveck *v);
void JASMIN_VERSION(polyveck_caddq)(polyveck *v);

void JASMIN_VERSION(polyveck_add)(polyveck *w, const polyveck *u, const polyveck *v);
void JASMIN_VERSION(polyveck_sub)(polyveck *w, const polyveck *u, const polyveck *v);
void JASMIN_VERSION(polyveck_shiftl)(polyveck *v);

void JASMIN_VERSION(polyveck_ntt)(polyveck *v);
void JASMIN_VERSION(polyveck_invntt_tomont)(polyveck *v);
void JASMIN_VERSION(polyveck_pointwise_poly_montgomery)(polyveck *r, const poly *a, const polyveck *v);

int JASMIN_VERSION(polyveck_chknorm)(const polyveck *v, int32_t B);

void JASMIN_VERSION(polyveck_power2round)(polyveck *v1, polyveck *v0, const polyveck *v);
void JASMIN_VERSION(polyveck_decompose)(polyveck *v1, polyveck *v0, const polyveck *v);
unsigned int JASMIN_VERSION(polyveck_make_hint)(polyveck *h,
        const polyveck *v0,
        const polyveck *v1);
void JASMIN_VERSION(polyveck_use_hint)(polyveck *w, const polyveck *u, const polyveck *h);

void JASMIN_VERSION(polyveck_pack_w1)(uint8_t r[K * POLYW1_PACKEDBYTES], const polyveck *w1);

void JASMIN_VERSION(polyvec_matrix_expand)(polyvecl mat[K], const uint8_t rho[SEEDBYTES]);

void JASMIN_VERSION(polyvec_matrix_pointwise_montgomery)(polyveck *t, const polyvecl mat[K], const polyvecl *v);

int main ()
{
  checkpolyvecluniform(CRHBYTES, PQCLEAN_VERSION(polyvecl_uniform_eta), JASMIN_VERSION(polyvecl_uniform_eta), "polyvecl_uniform_eta");
  checkpolyvecluniform(CRHBYTES, PQCLEAN_VERSION(polyvecl_uniform_gamma1), JASMIN_VERSION(polyvecl_uniform_gamma1), "polyvecl_uniform_gamma1");

  checkpolyvecl(PQCLEAN_VERSION(polyvecl_reduce), JASMIN_VERSION(polyvecl_reduce), "polyvecl_reduce");
  checkpolyvecl3(PQCLEAN_VERSION(polyvecl_add), JASMIN_VERSION(polyvecl_add), "polyvecl_add");
  checkpolyvecl(PQCLEAN_VERSION(polyvecl_ntt), JASMIN_VERSION(polyvecl_ntt), "polyvecl_ntt");
  checkpolyvecl(PQCLEAN_VERSION(polyvecl_invntt_tomont), JASMIN_VERSION(polyvecl_invntt_tomont), "polyvecl_invntt_tomont");
  checkpolyvecl_poly(PQCLEAN_VERSION(polyvecl_pointwise_poly_montgomery), JASMIN_VERSION(polyvecl_pointwise_poly_montgomery), "polyvecl_pointwise_poly_montgomery");
  checkpoly_polyvecl(PQCLEAN_VERSION(polyvecl_pointwise_acc_montgomery), JASMIN_VERSION(polyvecl_pointwise_acc_montgomery), "polyvecl_pointwise_acc_montgomery");
  checkpolyveclint(PQCLEAN_VERSION(polyvecl_chknorm), JASMIN_VERSION(polyvecl_chknorm), "polyvecl_chknorm");

  checkpolyveckuniform(CRHBYTES, PQCLEAN_VERSION(polyveck_uniform_eta), JASMIN_VERSION(polyveck_uniform_eta), "polyveck_uniform_eta");

  checkpolyveck(PQCLEAN_VERSION(polyveck_reduce), JASMIN_VERSION(polyveck_reduce), "polyveck_reduce");
  checkpolyveck(PQCLEAN_VERSION(polyveck_caddq), JASMIN_VERSION(polyveck_caddq), "polyveck_caddq");

  checkpolyveck3(PQCLEAN_VERSION(polyveck_add), JASMIN_VERSION(polyveck_add), "polyveck_add");
  checkpolyveck3(PQCLEAN_VERSION(polyveck_sub), JASMIN_VERSION(polyveck_sub), "polyveck_sub");
  checkpolyveck(PQCLEAN_VERSION(polyveck_shiftl), JASMIN_VERSION(polyveck_shiftl), "polyveck_shiftl");

  checkpolyveck(PQCLEAN_VERSION(polyveck_ntt), JASMIN_VERSION(polyveck_ntt), "polyveck_ntt");
  checkpolyveck(PQCLEAN_VERSION(polyveck_invntt_tomont), JASMIN_VERSION(polyveck_invntt_tomont), "polyveck_invntt_tomont");
  checkpolyveck_poly(PQCLEAN_VERSION(polyveck_pointwise_poly_montgomery), JASMIN_VERSION(polyveck_pointwise_poly_montgomery), "polyveck_pointwise_poly_montgomery");

  checkpolyveckint(PQCLEAN_VERSION(polyveck_chknorm), JASMIN_VERSION(polyveck_chknorm), "polyveck_chknorm");

  checkpolyveck3(PQCLEAN_VERSION(polyveck_power2round), JASMIN_VERSION(polyveck_power2round), "polyveck_power2round");
  checkpolyveck3(PQCLEAN_VERSION(polyveck_decompose), JASMIN_VERSION(polyveck_decompose), "polyveck_decompose");
  checkpolyveck3_u32(PQCLEAN_VERSION(polyveck_make_hint), JASMIN_VERSION(polyveck_make_hint), "polyveck_make_hint");
  checkpolyveck3(PQCLEAN_VERSION(polyveck_use_hint), JASMIN_VERSION(polyveck_use_hint), "polyveck_use_hint");

  checkpolyveckpackw1(PQCLEAN_VERSION(polyveck_pack_w1), JASMIN_VERSION(polyveck_pack_w1), "polyveck_pack_w1");

  checkmat(SEEDBYTES, PQCLEAN_VERSION(polyvec_matrix_expand), JASMIN_VERSION(polyvec_matrix_expand), "polyvec_matrix_expand");

  checkpolyvecl_mat(PQCLEAN_VERSION(polyvec_matrix_pointwise_montgomery), JASMIN_VERSION(polyvec_matrix_pointwise_montgomery), "polyvec_matrix_pointwise_montgomery");

  return 0;
}

