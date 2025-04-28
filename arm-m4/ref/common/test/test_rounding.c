#include "version.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "notrandombytes.c"
#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

int32_t PQCLEAN_VERSION(power2round)(int32_t *a0, int32_t a);
int32_t JASMIN_VERSION(power2round)(int32_t *a0, int32_t a);

int test_power2round()
{
  int32_t arg, a0_c, a0_jazz, a1_c, a1_jazz;

  for(int t=0; t<TESTS; t++)
  {
    // initialize 8 bytes of randomness
    randombytes((uint8_t*)(&arg), sizeof(int32_t));

    a1_c = PQCLEAN_VERSION(power2round)(&a0_c, arg);
    a1_jazz = JASMIN_VERSION(power2round)(&a0_jazz, arg);

    if (a0_c != a0_jazz) {
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, a0_c, a0_jazz);
      printf("FAIL: power2round a0\n");
      exit(1);
    }

    if (a1_c != a1_jazz) {
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, a1_c, a1_jazz);
      printf("FAIL: power2round a1\n");
      exit(1);
    }
  }

  printf("PASS: power2round\n");

  return 0;
}

int32_t PQCLEAN_VERSION(decompose)(int32_t *a0, int32_t a);
int32_t JASMIN_VERSION(decompose)(int32_t *a0, int32_t a);

int test_decompose()
{
  int32_t arg, a0_c, a0_jazz, a1_c, a1_jazz;

  for(int t=0; t<TESTS; t++)
  {
    // initialize 8 bytes of randomness
    randombytes((uint8_t*)(&arg), sizeof(int32_t));

    a1_c = PQCLEAN_VERSION(decompose)(&a0_c, arg);
    a1_jazz = JASMIN_VERSION(decompose)(&a0_jazz, arg);

    if (a0_c != a0_jazz) {
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, a0_c, a0_jazz);
      printf("FAIL: decompose a0\n");
      exit(1);
    }

    if (a1_c != a1_jazz) {
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, a1_c, a1_jazz);
      printf("FAIL: decompose a1\n");
      exit(1);
    }
  }

  printf("PASS: decompose\n");

  return 0;
}

int32_t PQCLEAN_VERSION(make_hint)(int32_t a0, int32_t a1);
int32_t JASMIN_VERSION(make_hint)(int32_t a0, int32_t a1);

int32_t PQCLEAN_VERSION(use_hint)(int32_t a0, unsigned int hint);
int32_t JASMIN_VERSION(use_hint)(int32_t a0, unsigned int hint);


int main ()
{
  test_power2round();
  test_decompose();
  check3232to32(PQCLEAN_VERSION(make_hint), JASMIN_VERSION(make_hint), "make_hint");
  check3232to32(PQCLEAN_VERSION(use_hint), JASMIN_VERSION(use_hint), "use_hint");
  return 0;
}

