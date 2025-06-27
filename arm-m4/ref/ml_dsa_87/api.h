#ifndef ML_DSA_87_API_H
#define ML_DSA_87_API_H

#define VERIFICATION_KEY_SIZE 2592
#define SIGNING_KEY_SIZE 4896
#define SIGNATURE_SIZE 4627

#include <stdint.h>
#include <stddef.h>

void ml_dsa_87_keygen(
  uint8_t verification_key[VERIFICATION_KEY_SIZE],
  uint8_t signing_key[SIGNING_KEY_SIZE],
  const uint8_t randomness[32]
);

int ml_dsa_87_sign(
  uint8_t signature[SIGNATURE_SIZE],
  uint8_t* context_message_randomness[3],
  const size_t contextlen_messagelen[2],
  const uint8_t signing_key[SIGNING_KEY_SIZE]
);

int ml_dsa_87_verify(
  uint8_t signature[SIGNATURE_SIZE],
  uint8_t* context_message[2],
  const size_t contextlen_messagelen[2],
  const uint8_t verification_key[VERIFICATION_KEY_SIZE]
);

#endif /* ML_DSA_87_API_H */

