#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#ifndef TESTS
#define TESTS 10000
#endif

extern void KeccakF1600_StatePermute_ref(uint32_t*);
extern void KeccakF1600_StatePermute_pqm4(uint32_t*);

void print_state(uint32_t *state)
{
  for(int i=0; i<50; i++)
  { printf("%08" PRIx32 " ", state[i]);
    if(i != 0 && (i+1) % 10 == 0) printf("\n");
  }
  printf("\n");
}

int main()
{
  uint32_t initial_state[50], ref_state[50], pqm4_state[50];
  size_t t;

  assert(sizeof(initial_state) == 200);

  memset(initial_state, 1, 200);

  for(t=0; t<TESTS; t++)
  { 
    memcpy(ref_state, initial_state, 200);
    memcpy(pqm4_state, initial_state, 200);

    KeccakF1600_StatePermute_ref(ref_state);
    KeccakF1600_StatePermute_pqm4(pqm4_state);

    assert(memcmp(ref_state, pqm4_state, 200) == 0);

    memcpy(initial_state, ref_state, 200);
  }

  print_state(initial_state);
  printf("OK\n");

  return 0;
}
