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

void PQCLEAN_DILITHIUM5_CLEAN_poly_ntt_jazz(poly *a);
void PQCLEAN_DILITHIUM5_CLEAN_poly_invntt_tomont_jazz(poly *a);
void PQCLEAN_DILITHIUM5_CLEAN_poly_pointwise_montgomery_jazz(poly *c, poly *a, poly *b);

int main ()
{
  checkpoly(PQCLEAN_DILITHIUM5_CLEAN_poly_reduce, PQCLEAN_DILITHIUM5_CLEAN_poly_reduce_jazz, "poly_reduce");
  checkpoly(PQCLEAN_DILITHIUM5_CLEAN_poly_caddq, PQCLEAN_DILITHIUM5_CLEAN_poly_caddq_jazz, "poly_caddq");
  checkpoly2(PQCLEAN_DILITHIUM5_CLEAN_poly_add, PQCLEAN_DILITHIUM5_CLEAN_poly_add_jazz, "poly_add");
  checkpoly2(PQCLEAN_DILITHIUM5_CLEAN_poly_add, PQCLEAN_DILITHIUM5_CLEAN_poly_add_inplace_jazz, "poly_add_inplace");
  checkpolyint(PQCLEAN_DILITHIUM5_CLEAN_poly_chknorm, PQCLEAN_DILITHIUM5_CLEAN_poly_chknorm, "poly_chknorm");
  return 0;
}
