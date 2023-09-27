#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "../randombytes/randombytes.h"

#define TESTS 20

int32_t reduce32(int32_t a);
int32_t reduce32_8380417_jazz(int32_t a);

int main () {
  int32_t arg;

  for(int t=0; t<TESTS; t++) {
    // initialize 4 bytes of randomness
    randombytes((uint8_t*)(&arg), sizeof(int32_t));

    int32_t res_c = reduce32(arg);
    int32_t res_jazz = reduce32_8380417_jazz(arg);

    if (res_c != res_jazz) {
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz);
      printf("FAIL: reduce32\n");
      exit(1);
    }
  }

  printf("PASS: reduce32\n");

  return 0;
}
