#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../randombytes/randombytes.h"

#define TESTS 20

int32_t freeze(int32_t a);
int32_t freeze_8380417_jazz(int32_t a);

int main () {
  int32_t arg;

  for(int t=0; t<TESTS; t++) {
    // initialize 4 bytes of randomness
    randombytes((uint8_t*)(&arg), sizeof(int32_t));

    int32_t res_c = freeze(arg);
    int32_t res_jazz = freeze_8380417_jazz(arg);

    if (res_c != res_jazz) {
      printf("%d -> %d != %d\n", arg, res_c, res_jazz);
      printf("FAIL: freeze\n");
      exit(1);
    }
  }

  printf("PASS: freeze\n");

  return 0;
}
