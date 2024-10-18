#ifndef JASMIN_MLDSA65_PACKING_WRAP_H
#define JASMIN_MLDSA65_PACKING_WRAP_H

#include <stdint.h>
#include <stddef.h>

#include "jasmin_params.h"

int JASMIN_MLDSA65_crypto_sign_verify_internal(const uint8_t *sig,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *pk);


int JASMIN_MLDSA65_crypto_sign_signature_ctx_internal(uint8_t sig[JASMIN_MLDSA65_CRYPTO_BYTES], uint8_t* m,  uint8_t* ctx, size_t siglen_mlen_ctxlen[3], uint8_t sk[JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES]);

int JASMIN_MLDSA65_crypto_sign_verify(const uint8_t *sig,
						     size_t siglen,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *pk)
{

  if (siglen != JASMIN_MLDSA65_CRYPTO_BYTES) {
        return -1;
  }

  return JASMIN_MLDSA65_crypto_sign_verify_internal(sig, m, mlen, pk);
}

int JASMIN_MLDSA65_crypto_sign_signature_ctx(uint8_t sig[JASMIN_MLDSA65_CRYPTO_BYTES], size_t *siglen, uint8_t* m, size_t mlen, uint8_t *ctx, size_t ctxlen, uint8_t sk[JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES])
{
  size_t siglen_mlen_ctxlen[3];
  siglen_mlen_ctxlen[0] = *siglen;
  siglen_mlen_ctxlen[1] = mlen;
  siglen_mlen_ctxlen[2] = ctxlen;

  return JASMIN_MLDSA65_crypto_sign_signature_ctx_internal(sig, m, ctx, siglen_mlen_ctxlen, sk);
}

#endif
