#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "notrandombytes.h"

#define DATA_POINTS 10000
#define MESSAGE_SIZE 129

static uint64_t checksum_update(uint64_t checksum, const uint8_t *data,
                                size_t data_len) {
  size_t i;

  for (i = 0; i < data_len; i++) {
    checksum ^= data[i];
    checksum *= 1099511628211ULL;
  }

  return checksum;
}

static uint64_t keygen_observations[DATA_POINTS];
static uint64_t sign_observations[DATA_POINTS];
static uint64_t verify_observations[DATA_POINTS];
static uint8_t empty_context[1] __attribute__((aligned(32)));
static uint8_t verification_key[BENCH_VERIFICATION_KEY_SIZE]
    __attribute__((aligned(32)));
static uint8_t signing_key[BENCH_SIGNING_KEY_SIZE]
    __attribute__((aligned(32)));
static uint8_t message[MESSAGE_SIZE] __attribute__((aligned(32)));
static struct {
  uint8_t bytes[BENCH_SIGNATURE_SIZE];
  uint64_t canary;
} signature_box __attribute__((aligned(32))) = {{0}, 0x0123456789abcdefULL};

static inline uint64_t cpucycles(void) {
  uint64_t result;

  asm volatile("lfence; rdtsc; shlq $32,%%rdx; orq %%rdx,%%rax; lfence"
               : "=a"(result)
               :
               : "%rdx", "memory");

  return result;
}

static int cmp_uint64(const void *a, const void *b) {
  const uint64_t lhs = *(const uint64_t *)a;
  const uint64_t rhs = *(const uint64_t *)b;

  if (lhs < rhs) {
    return -1;
  }
  if (lhs > rhs) {
    return 1;
  }
  return 0;
}

static uint64_t median(uint64_t *l, size_t llen) {
  qsort(l, llen, sizeof(uint64_t), cmp_uint64);

  if (llen % 2) {
    return l[llen / 2];
  }
  return (l[llen / 2 - 1] + l[llen / 2]) / 2;
}

static uint64_t average(const uint64_t *t, size_t tlen) {
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

int main(void) {
  uint8_t key_generation_randomness[32];
  uint8_t signing_randomness[32];
  uint8_t *signature = signature_box.bytes;

  const uint8_t *context_message_pointers[2] = {empty_context, message};
  const size_t context_message_sizes[2] = {0, MESSAGE_SIZE};

  uint64_t before, after;
  uint64_t cpucycles_overhead = overhead_of_cpucycles_call();
  uint64_t checksum;

  printf("name, median (cycles/ticks), average (cycles/ticks)\n");

  for (size_t i = 0; i < DATA_POINTS; i++) {
    notrandombytes(key_generation_randomness, sizeof(key_generation_randomness));

    before = cpucycles();
    if (bench_keygen(verification_key, signing_key,
                     key_generation_randomness) != 0) {
      return EXIT_FAILURE;
    }
    after = cpucycles();

    keygen_observations[i] = (after - cpucycles_overhead) - before;
  }

  for (size_t i = 0; i < DATA_POINTS; i++) {
    notrandombytes(signing_randomness, sizeof(signing_randomness));
    notrandombytes(message, sizeof(message));

    before = cpucycles();
    if (bench_sign(signature, signing_key, context_message_pointers,
                   context_message_sizes, signing_randomness) != 0) {
      return EXIT_FAILURE;
    }
    if (signature_box.canary != 0x0123456789abcdefULL) {
      return EXIT_FAILURE;
    }
    after = cpucycles();

    sign_observations[i] = (after - cpucycles_overhead) - before;
  }

  for (size_t i = 0; i < DATA_POINTS; i++) {
    before = cpucycles();
    if (bench_verify(verification_key, context_message_pointers,
                     context_message_sizes, signature) != 0) {
      return EXIT_FAILURE;
    }
    after = cpucycles();

    verify_observations[i] = (after - cpucycles_overhead) - before;
  }

  notrandombytes_reset();
  checksum = 1469598103934665603ULL;

  for (size_t i = 0; i < DATA_POINTS; i++) {
    notrandombytes(key_generation_randomness, sizeof(key_generation_randomness));

    if (bench_keygen(verification_key, signing_key, key_generation_randomness) != 0) {
      return EXIT_FAILURE;
    }

    checksum = checksum_update(checksum, verification_key,
                               BENCH_VERIFICATION_KEY_SIZE);
    checksum = checksum_update(checksum, signing_key, BENCH_SIGNING_KEY_SIZE);
  }

  for (size_t i = 0; i < DATA_POINTS; i++) {
    notrandombytes(signing_randomness, sizeof(signing_randomness));
    notrandombytes(message, sizeof(message));

    if (bench_sign(signature, signing_key, context_message_pointers,
                   context_message_sizes, signing_randomness) != 0) {
      return EXIT_FAILURE;
    }
    if (signature_box.canary != 0x0123456789abcdefULL) {
      return EXIT_FAILURE;
    }

    checksum = checksum_update(checksum, signature, BENCH_SIGNATURE_SIZE);
  }

  printf("%s, %llu, %llu\n", BENCH_KEYGEN_NAME,
         (unsigned long long)median(keygen_observations, DATA_POINTS),
         (unsigned long long)average(keygen_observations, DATA_POINTS));
  printf("%s, %llu, %llu\n", BENCH_SIGN_NAME,
         (unsigned long long)median(sign_observations, DATA_POINTS),
         (unsigned long long)average(sign_observations, DATA_POINTS));
  printf("%s, %llu, %llu\n", BENCH_VERIFY_NAME,
         (unsigned long long)median(verify_observations, DATA_POINTS),
         (unsigned long long)average(verify_observations, DATA_POINTS));
  printf("checksum, 0x%016llx\n", (unsigned long long)checksum);

  return EXIT_SUCCESS;
}
