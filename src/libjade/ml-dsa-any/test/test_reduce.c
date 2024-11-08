#include "version.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "notrandombytes.c"

#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

int32_t PQCLEAN_VERSION(montgomery_reduce)(int64_t a);
int32_t JASMIN_VERSION(montgomery_reduce)(int64_t a);

int32_t PQCLEAN_VERSION(reduce32)(int32_t a);
int32_t JASMIN_VERSION(reduce32)(int32_t a);

int32_t PQCLEAN_VERSION(caddq)(int32_t a);
int32_t JASMIN_VERSION(caddq)(int32_t a);

int32_t PQCLEAN_VERSION(freeze)(int32_t a);
int32_t JASMIN_VERSION(freeze)(int32_t a);

int main ()
{
  check64to32(PQCLEAN_VERSION(montgomery_reduce), JASMIN_VERSION(montgomery_reduce), "PQCLEAN_VERSION(montgomery_reduce");
  
  check32to32(PQCLEAN_VERSION(reduce32), JASMIN_VERSION(reduce32), "PQCLEAN_VERSION(reduce32");

  check32to32(PQCLEAN_VERSION(caddq), JASMIN_VERSION(caddq), "PQCLEAN_VERSION(caddq");
  
  check32to32(PQCLEAN_VERSION(freeze), JASMIN_VERSION(freeze), "PQCLEAN_VERSION(freeze");
  
  return 0;
}

