#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "poly.h"
#include "notrandombytes.c"

#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif

void PQCLEAN_DILITHIUM5_CLEAN_poly_reduce(poly *a); 
void PQCLEAN_DILITHIUM5_CLEAN_poly_reduce_jazz(poly *a); 

int main ()
{
  checkpoly(PQCLEAN_DILITHIUM5_CLEAN_poly_reduce, PQCLEAN_DILITHIUM5_CLEAN_poly_reduce_jazz, "poly_reduce");
  return 0;
}
