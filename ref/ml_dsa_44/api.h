#ifndef ML_DSA_65_API_H
#define ML_DSA_65_API_H

#define VERIFICATION_KEY_SIZE 1312
#define SIGNING_KEY_SIZE 2560
#define SIGNATURE_SIZE 2420

#include <stdint.h>
#include <stddef.h>

void ml_dsa_44_keygen(
  uint8_t verification_key[VERIFICATION_KEY_SIZE],
  uint8_t signing_key[SIGNING_KEY_SIZE],
  const uint8_t randomness[32]
);

void ml_dsa_44_sign(
  uint8_t signature[SIGNATURE_SIZE],
  const uint8_t signing_key[SIGNING_KEY_SIZE],
  const uint8_t *message,
  const size_t message_size,
  const uint8_t randomness[32]
);

int ml_dsa_44_verify(
  uint8_t verification_key[VERIFICATION_KEY_SIZE],
  const uint8_t *message,
  const size_t message_size,
  const uint8_t signature[SIGNATURE_SIZE]
);

#endif /* ML_DSA_65_API_H */

