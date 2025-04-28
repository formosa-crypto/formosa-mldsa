#include "version.h"

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

void JASMIN_VERSION(ntt)(int32_t a[N]);
void PQCLEAN_VERSION(ntt)(int32_t a[N]);

void JASMIN_VERSION(invntt_tomont)(int32_t a[N]);
void PQCLEAN_VERSION(invntt_tomont)(int32_t a[N]);

int main ()
{
  checkarrN(PQCLEAN_VERSION(ntt), JASMIN_VERSION(ntt), "ntt");
  checkarrN(PQCLEAN_VERSION(invntt_tomont), JASMIN_VERSION(invntt_tomont), "invntt_tomont");
  return 0;
}
