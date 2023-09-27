#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "../randombytes/randombytes.h"

#define TESTS 20

int32_t montgomery_reduce(int64_t a);
int32_t montgomery_reduce_8380417_jazz(int64_t a);

int main () {
  int64_t arg;

  for(int t=0; t<TESTS; t++) {
    // initialize 8 bytes of randomness
    randombytes((uint8_t*)(&arg), sizeof(int64_t));

    int32_t res_c = montgomery_reduce(arg);
    int32_t res_jazz = montgomery_reduce_8380417_jazz(arg);

    if (res_c != res_jazz) {
      printf("%" PRId64 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz);
      printf("FAIL: montgomery_reduce\n");
      exit(1);
    }
  }

  printf("PASS: montgomery_reduce\n");

  return 0;
}
