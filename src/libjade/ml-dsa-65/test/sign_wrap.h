#ifndef JASMIN_MLDSA65_PACKING_WRAP_H
#define JASMIN_MLDSA65_PACKING_WRAP_H

#include <stdint.h>
#include <stddef.h>

#include "jasmin_params.h"

extern int JASMIN_MLDSA65_crypto_sign_verify_internal(const uint8_t *sig,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *pk);


extern int JASMIN_MLDSA65_crypto_sign_signature_ctx_internal(uint8_t sig[JASMIN_MLDSA65_CRYPTO_BYTES], uint8_t* m_ctx[2], size_t ctxlen_mlen_siglen[3], uint8_t sk[JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES]);

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
  uint8_t* ctx_m[2];
  ctx_m[0] = ctx;
  ctx_m[1] = m;

  size_t ctxlen_mlen_siglen[3];
  ctxlen_mlen_siglen[0] = ctxlen;
  ctxlen_mlen_siglen[1] = mlen;
  ctxlen_mlen_siglen[2] = *siglen;

  return JASMIN_MLDSA65_crypto_sign_signature_ctx_internal(sig, ctx_m, ctxlen_mlen_siglen, sk);
}

#endif
