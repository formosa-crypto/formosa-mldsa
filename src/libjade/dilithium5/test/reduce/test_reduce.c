#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "notrandombytes.c"

#ifndef TESTS
#define TESTS 1000
#endif

int32_t PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce(int64_t a);
int32_t PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz(int64_t a);

int test_montgomery_reduce()
{
  int64_t arg;

  for(int t=0; t<TESTS; t++)
  {
    // initialize 8 bytes of randomness
    randombytes((uint8_t*)(&arg), sizeof(int64_t));

    int32_t res_c = PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce(arg);
    int32_t res_jazz = PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz(arg);

    if (res_c != res_jazz) {
      printf("%" PRId64 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz);
      printf("FAIL: montgomery_reduce\n");
      exit(1);
    }
  }

  printf("PASS: montgomery_reduce\n");

  return 0;
}

int32_t PQCLEAN_DILITHIUM5_CLEAN_reduce32(int32_t a);
int32_t PQCLEAN_DILITHIUM5_CLEAN_reduce32_jazz(int32_t a);

int test_reduce32()
{
  int32_t arg;

  for(int t=0; t<TESTS; t++)
  {
    // initialize 8 bytes of randomness
    randombytes((uint8_t*)(&arg), sizeof(int32_t));

    int32_t res_c = PQCLEAN_DILITHIUM5_CLEAN_reduce32(arg);
    int32_t res_jazz = PQCLEAN_DILITHIUM5_CLEAN_reduce32_jazz(arg);

    if (res_c != res_jazz) {
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz);
      printf("FAIL: reduce32\n");
      exit(1);
    }
  }

  printf("PASS: reduce32\n");

  return 0;
}


int main ()
{
  test_montgomery_reduce();
  test_reduce32();
  return 0;
}

