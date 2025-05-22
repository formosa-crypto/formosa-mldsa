#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pqclean_ml_dsa_65_avx2/api.h"
#include "notrandombytes.h"

#define DATA_POINTS 10000

#define MESSAGE_SIZE 127

// Utility functions and macros.

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

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
  uint8_t key_generation_randomness[32];
  uint8_t signing_randomness[32];

  uint8_t verification_key[PQCLEAN_MLDSA65_AVX2_CRYPTO_PUBLICKEYBYTES];
  uint8_t signing_key[PQCLEAN_MLDSA65_AVX2_CRYPTO_SECRETKEYBYTES];

  uint8_t message[MESSAGE_SIZE];
  uint8_t signature[PQCLEAN_MLDSA65_AVX2_CRYPTO_BYTES];
  size_t signature_size;

  uint64_t observations[DATA_POINTS] = {0};

  uint64_t before, after;

  uint64_t cpucycles_overhead = overhead_of_cpucycles_call();

  printf("name, median (cycles/ticks), average (cycles/ticks)\n");

  // Benchmark key-generation.
  for (size_t i = 0; i < DATA_POINTS; i++) {
    notrandombytes(key_generation_randomness, 32);

    before = cpucycles();
    PQCLEAN_MLDSA65_AVX2_crypto_sign_keypair(verification_key, signing_key, key_generation_randomness);
    after = cpucycles();

    observations[i] = (after - cpucycles_overhead) - before;
  }
  printf("%s, %llu, %llu\n",
         "PQClean ML-DSA-65 AVX2 key-generation",
         (unsigned long long)median(observations, DATA_POINTS),
         (unsigned long long)average(observations, DATA_POINTS));

  // Benchmark signing.
  for (size_t i = 0; i < DATA_POINTS; i++) {
    notrandombytes(signing_randomness, 32);
    notrandombytes(message, MESSAGE_SIZE);

    before = cpucycles();
    PQCLEAN_MLDSA65_AVX2_crypto_sign_signature_ctx(signature, &signature_size, message, sizeof(message), NULL, 0, signing_key, signing_randomness);
    after = cpucycles();

    observations[i] = (after - cpucycles_overhead) - before;
  }
  printf("%s, %llu, %llu\n",
         "PQClean ML-DSA-65 AVX2 signing",
         (unsigned long long)median(observations, DATA_POINTS),
         (unsigned long long)average(observations, DATA_POINTS));

  // Benchmark verification.
  for (size_t i = 0; i < DATA_POINTS; i++) {
    before = cpucycles();
    PQCLEAN_MLDSA65_AVX2_crypto_sign_verify_ctx(signature, PQCLEAN_MLDSA65_AVX2_CRYPTO_BYTES, message, sizeof(message), NULL, 0, verification_key);
    after = cpucycles();

    observations[i] = (after - cpucycles_overhead) - before;
  }
  printf("%s, %llu, %llu\n",
         "PQClean ML-DSA-65 AVX2 verification",
         (unsigned long long)median(observations, DATA_POINTS),
         (unsigned long long)average(observations, DATA_POINTS));

  return EXIT_SUCCESS;
}
