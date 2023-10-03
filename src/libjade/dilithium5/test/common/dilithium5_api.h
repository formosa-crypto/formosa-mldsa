#ifndef JADE_SIGN_dilithium_dilithium5_armv7m_clean_API_H
#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_API_H

#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_PUBLICKEYBYTES  2592
#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_SECRETKEYBYTES  4864
#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_BYTES           4595
#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_DETERMINISTIC   1

#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_ALGNAME         "Dilithium5"
#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_ARCH            "armv7m"
#define JADE_SIGN_dilithium_dilithium5_armv7m_clean_IMPL            "clean"

#include <stdint.h>
#include <stddef.h>

int jade_sign_dilithium_dilithium5_armv7m_clean_keypair(
  uint8_t *public_key,
  uint8_t *secret_key
);

int jade_sign_dilithium_dilithium5_armv7m_clean(
  uint8_t *signed_message,
  size_t *signed_message_length,
  const uint8_t *message,
  size_t message_length,
  const uint8_t *secret_key
);

int jade_sign_dilithium_dilithium5_armv7m_clean_open(
  uint8_t *message,
  size_t *message_length,
  const uint8_t *signed_message,
  size_t signed_message_length,
  const uint8_t *public_key
);

#endif

