#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_POINTS 1000

// Utility functions and macros.

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

extern void ntt_wrapper(uint32_t polynomial[256]);

static inline uint64_t cpucycles(void) {
  uint64_t result;

  asm volatile("rdtsc; shlq $32,%%rdx; orq %%rdx,%%rax"
               : "=a"(result)
               :
               : "%rdx");

  return result;
}

static int cmp_uint64(const void *a, const void *b) {
  if (*(uint64_t *)a < *(uint64_t *)b) {
    return -1;
  }
  if (*(uint64_t *)a > *(uint64_t *)b) {
    return 1;
  }
  return 0;
}

static uint64_t median(uint64_t *l, size_t llen) {
  qsort(l, llen, sizeof(uint64_t), cmp_uint64);

  if (llen % 2) {
    return l[llen / 2];
  } else {
    return (l[llen / 2 - 1] + l[llen / 2]) / 2;
  }
}

static uint64_t average(uint64_t *t, size_t tlen) {
  size_t i;
  uint64_t acc = 0;

  for (i = 0; i < tlen; i++) {
    acc += t[i];
  }

  return acc / tlen;
}

static uint64_t overhead_of_cpucycles_call(void) {
  uint64_t t0, t1, overhead = -1LL;
  unsigned int i;

  for (i = 0; i < 100000; i++) {
    t0 = cpucycles();
    __asm__ volatile("");
    t1 = cpucycles();
    if (t1 - t0 < overhead) {
      overhead = t1 - t0;
    }
  }

  return overhead;
}

// Now for the actual benchmarking.

int main(void) {
  uint32_t polynomial[256];

  uint64_t observations[DATA_POINTS] = {0};

  uint64_t before, after;

  uint64_t cpucycles_overhead = overhead_of_cpucycles_call();

  // Benchmark key-generation.
  for (size_t i = 0; i < DATA_POINTS; i++) {
    before = cpucycles();
    ntt_wrapper(polynomial);
    after = cpucycles();

    observations[i] = (after - cpucycles_overhead) - before;
  }
  printf("median (cycles/ticks), average (cycles/ticks)\n");
  printf("%llu, %llu\n",
         (unsigned long long)median(observations, DATA_POINTS),
         (unsigned long long)average(observations, DATA_POINTS));

  return EXIT_SUCCESS;
}
