#ifndef PQCLEAN_DILITHIUM5_CLEAN_PACKING_WRAP_H
#define PQCLEAN_DILITHIUM5_CLEAN_PACKING_WRAP_H
#include "params.h"
#include "packing.h"
#include <stdint.h>

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify_internal_jazz(const uint8_t *sig,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *pk);

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify_jazz(const uint8_t *sig,
						     size_t siglen,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *pk)
{

  if (siglen != PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES) {
        return -1;
  }
  
  return PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify_internal_jazz(sig, m, mlen, pk);
}


#endif
