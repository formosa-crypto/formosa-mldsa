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

int32_t JASMIN_MLDSA44_mul_montgomery_reduce(int32_t x, int32_t y);

int32_t PQCLEAN_MLDSA44_CLEAN_mul_montgomery_reduce_8380417(int32_t x, int32_t y)
{
  return PQCLEAN_MLDSA44_CLEAN_montgomery_reduce((int64_t) x * y);
}

void JASMIN_MLDSA44_ntt(int32_t a[N]);
void PQCLEAN_MLDSA44_CLEAN_ntt(int32_t a[N]);

void JASMIN_MLDSA44_invntt_tomont(int32_t a[N]);
void PQCLEAN_MLDSA44_CLEAN_invntt_tomont(int32_t a[N]);

int main ()
{
  check3232to32(PQCLEAN_MLDSA44_CLEAN_mul_montgomery_reduce_8380417, JASMIN_MLDSA44_mul_montgomery_reduce, "JASMIN_MLDSA44_mul_montgomery_reduce_8380417");
  checkarrN(PQCLEAN_MLDSA44_CLEAN_ntt, JASMIN_MLDSA44_ntt, "ntt");
  checkarrN(PQCLEAN_MLDSA44_CLEAN_invntt_tomont, JASMIN_MLDSA44_invntt_tomont, "invntt_tomont");
  return 0;
}
