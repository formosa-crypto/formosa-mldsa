#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "poly.h"
#include "notrandombytes.c"
#include "fips202.h"
#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif


void PQCLEAN_DILITHIUM5_CLEAN_poly_reduce_jazz(poly *a);
void PQCLEAN_DILITHIUM5_CLEAN_poly_caddq_jazz(poly *a);
void PQCLEAN_DILITHIUM5_CLEAN_poly_add_jazz(poly *c, poly *a, poly *b);
void PQCLEAN_DILITHIUM5_CLEAN_poly_add_inplace_jazz(poly *c, poly *a, poly *b);
void PQCLEAN_DILITHIUM5_CLEAN_poly_chknorm(poly *a, int32_t B);

void JASMIN_DILITHIUM5_poly_ntt(poly *a);
void JASMIN_DILITHIUM5_poly_invntt_tomont(poly *a);
void JASMIN_DILITHIUM5_poly_pointwise_montgomery(poly *c, poly *a, poly *b);
uint32_t JASMIN_DILITHIUM5_poly_make_hint(poly *h, poly *a0, poly *a1);
void JASMIN_DILITHIUM5_poly_power2round(poly *a1, poly *a0, poly *a);

void JASMIN_DILITHIUM5_poly_shiftl(poly *a);
void JASMIN_DILITHIUM5_poly_sub(poly *c, poly *a, poly *b);

void JASMIN_DILITHIUM5_polyt0_pack(uint8_t *r, const poly *a);
void JASMIN_DILITHIUM5_polyt0_unpack(poly *r, const uint8_t *a);
void JASMIN_DILITHIUM5_polyt1_pack(uint8_t *r, const poly *a);
void JASMIN_DILITHIUM5_polyt1_unpack(poly *r, const uint8_t *a);

void JASMIN_DILITHIUM5_poly_use_hint(poly *b, poly *a, poly *h);

void JASMIN_DILITHIUM5_polyw1_pack(uint8_t *r, const poly *a);

void JASMIN_DILITHIUM5_polyz_pack(uint8_t *r, const poly *a);
void JASMIN_DILITHIUM5_polyz_unpack(poly *r, const uint8_t *a);
void JASMIN_DILITHIUM5_poly_uniform(poly * a, const uint8_t *seed, uint16_t nonce);
void JASMIN_DILITHIUM5_poly_uniform_eta(poly * a, const uint8_t *seed, uint16_t nonce);
void JASMIN_DILITHIUM5_poly_uniform_gamma1(poly * a, const uint8_t *seed, uint16_t nonce);



int main ()
{
  checkpoly(PQCLEAN_DILITHIUM5_CLEAN_poly_reduce, PQCLEAN_DILITHIUM5_CLEAN_poly_reduce_jazz, "poly_reduce");
  checkpoly(PQCLEAN_DILITHIUM5_CLEAN_poly_caddq, PQCLEAN_DILITHIUM5_CLEAN_poly_caddq_jazz, "poly_caddq");
  checkpoly2(PQCLEAN_DILITHIUM5_CLEAN_poly_add, PQCLEAN_DILITHIUM5_CLEAN_poly_add_jazz, "poly_add");
  checkpoly2(PQCLEAN_DILITHIUM5_CLEAN_poly_add, PQCLEAN_DILITHIUM5_CLEAN_poly_add_inplace_jazz, "poly_add_inplace");
  checkpolyint(PQCLEAN_DILITHIUM5_CLEAN_poly_chknorm, PQCLEAN_DILITHIUM5_CLEAN_poly_chknorm, "poly_chknorm");
  return 0;
}
