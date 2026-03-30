#include <stddef.h>
#include <stdint.h>

#define MLD_CONFIG_PARAMETER_SET 65
#include "mldsa-native/mldsa/mldsa_native.h"

#define BENCH_VERIFICATION_KEY_SIZE CRYPTO_PUBLICKEYBYTES
#define BENCH_SIGNING_KEY_SIZE CRYPTO_SECRETKEYBYTES
#define BENCH_SIGNATURE_SIZE CRYPTO_BYTES

#define BENCH_KEYGEN_NAME "mldsa-native ML-DSA-65 key-generation"
#define BENCH_SIGN_NAME "mldsa-native ML-DSA-65 signing"
#define BENCH_VERIFY_NAME "mldsa-native ML-DSA-65 verification"

static size_t bench_signature_size = 0;
static const uint8_t *bench_randomness = NULL;
static size_t bench_randomness_size = 0;

int randombytes(uint8_t *out, size_t outlen) {
  if (bench_randomness == NULL || outlen != bench_randomness_size) {
    return -1;
  }

  for (size_t i = 0; i < outlen; i++) {
    out[i] = bench_randomness[i];
  }

  return 0;
}

static int bench_keygen(uint8_t *verification_key, uint8_t *signing_key,
                        const uint8_t randomness[32]) {
  int rc;

  bench_randomness = randomness;
  bench_randomness_size = 32;
  rc = crypto_sign_keypair(verification_key, signing_key);
  bench_randomness = NULL;
  bench_randomness_size = 0;

  return rc;
}

static int bench_sign(uint8_t *signature, const uint8_t *signing_key,
                      const uint8_t *context_message_pointers[2],
                      const size_t context_message_sizes[2],
                      const uint8_t randomness[32]) {
  int rc;

  bench_randomness = randomness;
  bench_randomness_size = 32;
  rc = crypto_sign_signature(signature, &bench_signature_size,
                             context_message_pointers[1],
                             context_message_sizes[1],
                             context_message_pointers[0],
                             context_message_sizes[0], signing_key);
  bench_randomness = NULL;
  bench_randomness_size = 0;

  return rc;
}

static int bench_verify(const uint8_t *verification_key,
                        const uint8_t *context_message_pointers[2],
                        const size_t context_message_sizes[2],
                        const uint8_t *signature) {
  return crypto_sign_verify(signature, bench_signature_size,
                            context_message_pointers[1],
                            context_message_sizes[1],
                            context_message_pointers[0],
                            context_message_sizes[0], verification_key);
}

#include "bench_common.c"
