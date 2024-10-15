#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "notrandombytes.c"

#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

int32_t PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce(int64_t a);
int32_t JASMIN_DILITHIUM5_montgomery_reduce(int64_t a);

int32_t PQCLEAN_DILITHIUM5_CLEAN_reduce32(int32_t a);
int32_t JASMIN_DILITHIUM5_reduce32(int32_t a);

int32_t PQCLEAN_DILITHIUM5_CLEAN_caddq(int32_t a);
int32_t JASMIN_DILITHIUM5_caddq(int32_t a);

int32_t PQCLEAN_DILITHIUM5_CLEAN_freeze(int32_t a);
int32_t JASMIN_DILITHIUM5_freeze(int32_t a);

int main ()
{
  check64to32(PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce, JASMIN_DILITHIUM5_montgomery_reduce, "PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce");
  
  check32to32(PQCLEAN_DILITHIUM5_CLEAN_reduce32, JASMIN_DILITHIUM5_reduce32, "PQCLEAN_DILITHIUM5_CLEAN_reduce32");

  check32to32(PQCLEAN_DILITHIUM5_CLEAN_caddq, JASMIN_DILITHIUM5_caddq, "PQCLEAN_DILITHIUM5_CLEAN_caddq");
  
  check32to32(PQCLEAN_DILITHIUM5_CLEAN_freeze, JASMIN_DILITHIUM5_freeze, "PQCLEAN_DILITHIUM5_CLEAN_freeze");
  
  return 0;
}

