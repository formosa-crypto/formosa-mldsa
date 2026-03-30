#include <stddef.h>
#include <stdint.h>

#include "api.h"

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

#define BENCH_VERIFICATION_KEY_SIZE VERIFICATION_KEY_SIZE
#define BENCH_SIGNING_KEY_SIZE SIGNING_KEY_SIZE
#define BENCH_SIGNATURE_SIZE SIGNATURE_SIZE

#define BENCH_KEYGEN_NAME STRINGIFY(KEYGEN) "_" STRINGIFY(IMPLEMENTATION_TYPE)
#define BENCH_SIGN_NAME STRINGIFY(SIGN) "_" STRINGIFY(IMPLEMENTATION_TYPE)
#define BENCH_VERIFY_NAME STRINGIFY(VERIFY) "_" STRINGIFY(IMPLEMENTATION_TYPE)

typedef int (*bench_sign_abi_fn)(
    uint8_t signature[SIGNATURE_SIZE],
    const uint8_t signing_key[SIGNING_KEY_SIZE], const uint64_t context[2],
    uintptr_t message_pointer, size_t message_size,
    const uint8_t randomness[32]);

typedef int (*bench_verify_abi_fn)(
    uint8_t verification_key[VERIFICATION_KEY_SIZE], const uint64_t context[2],
    uintptr_t message_pointer, size_t message_size,
    const uint8_t signature[SIGNATURE_SIZE]);

static int bench_keygen(uint8_t *verification_key, uint8_t *signing_key,
                        const uint8_t randomness[32]) {
  KEYGEN(verification_key, signing_key, randomness);
  return 0;
}

static int bench_sign(uint8_t *signature, const uint8_t *signing_key,
                      const uint8_t *context_message_pointers[2],
                      const size_t context_message_sizes[2],
                      const uint8_t randomness[32]) {
  const uint64_t context[2] = {(uint64_t)(uintptr_t)context_message_pointers[0],
                               (uint64_t)context_message_sizes[0]};
  bench_sign_abi_fn sign_fn = (bench_sign_abi_fn)SIGN;

  return sign_fn(signature, signing_key, context,
                 (uintptr_t)context_message_pointers[1],
                 context_message_sizes[1], randomness);
}

static int bench_verify(const uint8_t *verification_key,
                        const uint8_t *context_message_pointers[2],
                        const size_t context_message_sizes[2],
                        const uint8_t *signature) {
  const uint64_t context[2] = {(uint64_t)(uintptr_t)context_message_pointers[0],
                               (uint64_t)context_message_sizes[0]};
  bench_verify_abi_fn verify_fn = (bench_verify_abi_fn)VERIFY;

  return verify_fn((uint8_t *)verification_key, context,
                   (uintptr_t)context_message_pointers[1],
                   context_message_sizes[1], signature);
}

#include "bench_common.c"
