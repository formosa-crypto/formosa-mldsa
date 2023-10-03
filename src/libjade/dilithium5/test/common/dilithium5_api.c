#include "dilithium5_api.h"
#include "api.h"

int jade_sign_dilithium_dilithium5_armv7m_clean_keypair(
  uint8_t *public_key,
  uint8_t *secret_key
)
{
  return PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair(public_key, secret_key);
}

int jade_sign_dilithium_dilithium5_armv7m_clean(
  uint8_t *signed_message,
  size_t *signed_message_length,
  const uint8_t *message,
  size_t message_length,
  const uint8_t *secret_key
)
{
  return PQCLEAN_DILITHIUM5_CLEAN_crypto_sign(signed_message, signed_message_length, message, message_length, secret_key);
}

int jade_sign_dilithium_dilithium5_armv7m_clean_open(
  uint8_t *message,
  size_t *message_length,
  const uint8_t *signed_message,
  size_t signed_message_length,
  const uint8_t *public_key
)
{
  return PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_open(message, message_length, signed_message, signed_message_length, public_key);
}

