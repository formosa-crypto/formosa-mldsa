#ifndef PQCLEAN_DILITHIUM5_CLEAN_PACKING_WRAP_H
#define PQCLEAN_DILITHIUM5_CLEAN_PACKING_WRAP_H

#include <stdint.h>
#include <stddef.h>

#include "../../params.h"

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify_internal(const uint8_t *sig,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *pk);


int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature_internal(uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES], uint8_t* m,  size_t siglen_mlen[2], uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES]);

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify(const uint8_t *sig,
						     size_t siglen,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *pk)
{

  if (siglen != PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES) {
        return -1;
  }

  return PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify_internal(sig, m, mlen, pk);
}

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature(uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES], size_t *siglen, uint8_t* m, size_t mlen, uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES])
{
  size_t siglen_mlen[2];
  siglen_mlen[0] = *siglen;
  siglen_mlen[1] = mlen;

  return PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature_internal(sig, m, siglen_mlen, sk);
}

#endif
