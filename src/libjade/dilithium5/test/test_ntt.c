#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "notrandombytes.c"

#ifndef TESTS
#define TESTS 1000
#endif

void PQCLEAN_DILITHIUM5_CLEAN_ntt(int32_t a[N]);
void PQCLEAN_DILITHIUM5_CLEAN_ntt_jazz(int32_t a[N]);

void PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont(int32_t a[N]);
void PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont_jazz(int32_t a[N]);

int test_ntt()
{
  int32_t arg;
  int32_t a[N];
  int32_t a_jazz[N];

  for(int t=0; t<TESTS; t++)
  {
    // initialize 8 bytes of randomness
    for (int i = 0; i < N; i++) {
      randombytes((uint8_t*)(&arg), sizeof(int32_t));
      a[i] = arg;
      a_jazz[i] = arg;
    }

    PQCLEAN_DILITHIUM5_CLEAN_ntt(a);
    PQCLEAN_DILITHIUM5_CLEAN_ntt_jazz(a);

    for (int i = 0; i < N; i++) {
      if (a[i] != a_jazz[i]) {
        printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", (int32_t)arg, a[i], a_jazz[i]);
        printf("FAIL: ntt\n");
        exit(1);
      }
    }
  }

  printf("PASS: ntt\n");

  return 0;
}

int test_invntt_tomont()
{
  int32_t arg;
  int32_t a[N];
  int32_t a_jazz[N];

  for(int t=0; t<TESTS; t++)
  {
    // initialize 8 bytes of randomness
    for (int i = 0; i < N; i++) {
      randombytes((uint8_t*)(&arg), sizeof(int32_t));
      a[i] = arg;
      a_jazz[i] = arg;
    }

    PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont(a);
    PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont_jazz(a);

    for (int i = 0; i < N; i++) {
      if (a[i] != a_jazz[i]) {
        printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", (int32_t)arg, a[i], a_jazz[i]);
        printf("FAIL: ntt\n");
        exit(1);
      }
    }
  }

  printf("PASS: invntt_tomont\n");

  return 0;
}

int main ()
{
  test_ntt();
  test_invntt_tomont();
  return 0;
}
