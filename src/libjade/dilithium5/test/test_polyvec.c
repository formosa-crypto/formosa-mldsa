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

int main ()
{
  checkpolyvecluniform(CRHBYTES, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_eta, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_eta_jazz, "polyvecl_uniform_eta");
  checkpolyvecluniform(CRHBYTES, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_gamma1, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_gamma1_jazz, "polyvecl_uniform_gamma1");

  checkpolyvecl(PQCLEAN_DILITHIUM5_CLEAN_polyvecl_reduce, PQCLEAN_DILITHIUM5_CLEAN_polyvecl_reduce_jazz, "polyvecl_reduce");
  return 0;
}

