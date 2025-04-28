#ifndef JASMIN_MLDSA_SIGN_WRAP_H
#define JASMIN_MLDSA_SIGN_WRAP_H

#include "version.h"

#include <stdint.h>
#include <stddef.h>

#include "jasmin_params.h"

extern int JASMIN_VERSION(crypto_sign_signature_ctx_internal)(uint8_t sig[JASMIN_VERSION(CRYPTO_BYTES)], const uint8_t* ctx_m[2], size_t ctxlen_mlen_siglen[3], uint8_t sk[JASMIN_VERSION(CRYPTO_SECRETKEYBYTES)]);
extern int JASMIN_VERSION(crypto_sign_signature_ctx_seed_internal)(uint8_t sig[JASMIN_VERSION(CRYPTO_BYTES)], const uint8_t* ctx_m_rand[3], size_t ctxlen_mlen_siglen[3], uint8_t sk[JASMIN_VERSION(CRYPTO_SECRETKEYBYTES)]);
extern int JASMIN_VERSION(crypto_sign_verify_ctx_internal)(const uint8_t *sig, const uint8_t* ctx_m[2], size_t ctxlen_mlen_siglen[3], const uint8_t *pk);

int JASMIN_VERSION(crypto_sign_signature_ctx)(uint8_t sig[JASMIN_VERSION(CRYPTO_BYTES)], size_t *siglen, uint8_t* m, size_t mlen, uint8_t *ctx, size_t ctxlen, uint8_t sk[JASMIN_VERSION(CRYPTO_SECRETKEYBYTES)])
{
  const uint8_t* ctx_m[2];
  ctx_m[0] = ctx;
  ctx_m[1] = m;

  size_t ctxlen_mlen_siglen[3];
  ctxlen_mlen_siglen[0] = ctxlen;
  ctxlen_mlen_siglen[1] = mlen;
  ctxlen_mlen_siglen[2] = *siglen;

  return JASMIN_VERSION(crypto_sign_signature_ctx_internal)(sig, ctx_m, ctxlen_mlen_siglen, sk);
}

int JASMIN_VERSION(crypto_sign_signature_ctx_seed)(uint8_t sig[JASMIN_VERSION(CRYPTO_BYTES)], size_t *siglen, uint8_t* m, size_t mlen, uint8_t *ctx, size_t ctxlen, uint8_t sk[JASMIN_VERSION(CRYPTO_SECRETKEYBYTES)], uint8_t rand[RNDBYTES])
{
  const uint8_t* ctx_m_rand[3];
  ctx_m_rand[0] = ctx;
  ctx_m_rand[1] = m;
  ctx_m_rand[2] = rand;

  size_t ctxlen_mlen_siglen[3];
  ctxlen_mlen_siglen[0] = ctxlen;
  ctxlen_mlen_siglen[1] = mlen;
  ctxlen_mlen_siglen[2] = *siglen;

  return JASMIN_VERSION(crypto_sign_signature_ctx_seed_internal)(sig, ctx_m_rand, ctxlen_mlen_siglen, sk);
}

int JASMIN_VERSION(crypto_sign_verify_ctx)(const uint8_t *sig,
						     size_t siglen,
						     const uint8_t *m,
						     size_t mlen,
						     const uint8_t *ctx,
						     size_t ctxlen,
						     const uint8_t *pk)
{

  if (siglen != JASMIN_VERSION(CRYPTO_BYTES)) {
        return -1;
  }

  const uint8_t* ctx_m[2];
  ctx_m[0] = ctx;
  ctx_m[1] = m;

  size_t ctxlen_mlen_siglen[3];
  ctxlen_mlen_siglen[0] = ctxlen;
  ctxlen_mlen_siglen[1] = mlen;
  ctxlen_mlen_siglen[2] = siglen;

  return JASMIN_VERSION(crypto_sign_verify_ctx_internal)(sig, ctx_m, ctxlen_mlen_siglen, pk);
}

#endif
