#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "notrandombytes.c"

#include "reduce.h"
#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

int32_t PQCLEAN_DILITHIUM5_CLEAN_mul_montgomery_reduce_jazz(int32_t x, int32_t y);

int32_t PQCLEAN_DILITHIUM5_CLEAN_mul_montgomery_reduce_8380417(int32_t x, int32_t y)
{
  return PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce((int64_t) x * y);
}

void PQCLEAN_DILITHIUM5_CLEAN_ntt(int32_t a[N]);
void PQCLEAN_DILITHIUM5_CLEAN_ntt_jazz(int32_t a[N]);

void PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont(int32_t a[N]);
void PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont_jazz(int32_t a[N]);

int main ()
{
  check3232to32(PQCLEAN_DILITHIUM5_CLEAN_mul_montgomery_reduce_8380417, PQCLEAN_DILITHIUM5_CLEAN_mul_montgomery_reduce_jazz, "PQCLEAN_DILITHIUM5_CLEAN_mul_montgomery_reduce_8380417");
  checkpoly(PQCLEAN_DILITHIUM5_CLEAN_ntt, PQCLEAN_DILITHIUM5_CLEAN_ntt_jazz, "ntt"); 
  checkpoly(PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont, PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont_jazz, "invntt_tomont"); 
  return 0;
}
