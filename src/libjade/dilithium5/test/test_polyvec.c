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


  return 0;
}

