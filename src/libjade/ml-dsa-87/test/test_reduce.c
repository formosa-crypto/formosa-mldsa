#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "notrandombytes.c"

#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

int32_t PQCLEAN_MLDSA65_CLEAN_montgomery_reduce(int64_t a);
int32_t JASMIN_MLDSA65_montgomery_reduce(int64_t a);

int32_t PQCLEAN_MLDSA65_CLEAN_reduce32(int32_t a);
int32_t JASMIN_MLDSA65_reduce32(int32_t a);

int32_t PQCLEAN_MLDSA65_CLEAN_caddq(int32_t a);
int32_t JASMIN_MLDSA65_caddq(int32_t a);

int32_t PQCLEAN_MLDSA65_CLEAN_freeze(int32_t a);
int32_t JASMIN_MLDSA65_freeze(int32_t a);

int main ()
{
  check64to32(PQCLEAN_MLDSA65_CLEAN_montgomery_reduce, JASMIN_MLDSA65_montgomery_reduce, "PQCLEAN_MLDSA65_CLEAN_montgomery_reduce");
  
  check32to32(PQCLEAN_MLDSA65_CLEAN_reduce32, JASMIN_MLDSA65_reduce32, "PQCLEAN_MLDSA65_CLEAN_reduce32");

  check32to32(PQCLEAN_MLDSA65_CLEAN_caddq, JASMIN_MLDSA65_caddq, "PQCLEAN_MLDSA65_CLEAN_caddq");
  
  check32to32(PQCLEAN_MLDSA65_CLEAN_freeze, JASMIN_MLDSA65_freeze, "PQCLEAN_MLDSA65_CLEAN_freeze");
  
  return 0;
}

