#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define DATA_POINTS 10000

extern void KEYGEN(uint8_t *verification_key, uint8_t *signing_key,
                   const uint8_t key_generation_randomness[32]);
extern void SIGN(uint8_t *signature, const uint8_t *signing_key,
                 const uint8_t *message, const size_t message_size,
                 const uint8_t randomness[32]);
extern void VERIFY(const uint8_t *verification_key, const uint8_t *message,
                   const size_t message_size,
                   const uint8_t signature[SIGNATURE_SIZE]);

int main(void) {
  uint8_t key_generation_randomness[32];
  uint8_t signing_randomness[32];

  uint8_t verification_key[VERIFICATION_KEY_SIZE];
  uint8_t signing_key[SIGNING_KEY_SIZE];

  uint8_t message[64] = {0};
  uint8_t signature[SIGNATURE_SIZE];

  uint64_t observations[DATA_POINTS], i;

  for (size_t i = 0; i < 32; i++) {
    key_generation_randomness[i] = i;
    signing_randomness[i] = i;
  }

  printf("name, median (cycles/ticks), average (cycles/ticks)\n");

  // Benchmark key-generation.
  for (i = 0; i < DATA_POINTS; i++) {
    observations[i] = cpucycles();
    KEYGEN(verification_key, signing_key, key_generation_randomness);
  }
  print_results(STRINGIFY(FORMATTED_NAME(KEYGEN)), observations, DATA_POINTS);

  // Benchmark signing.
  for (i = 0; i < DATA_POINTS; i++) {
    observations[i] = cpucycles();
    SIGN(signature, signing_key, message, sizeof(message), signing_randomness);
  }
  print_results(STRINGIFY(FORMATTED_NAME(SIGN)), observations, DATA_POINTS);

  // Benchmark verification.
  for (i = 0; i < DATA_POINTS; i++) {
    observations[i] = cpucycles();
    VERIFY(verification_key, message, sizeof(message), signature);
  }
  print_results(STRINGIFY(FORMATTED_NAME(VERIFY)), observations, DATA_POINTS);

  return EXIT_SUCCESS;
}
