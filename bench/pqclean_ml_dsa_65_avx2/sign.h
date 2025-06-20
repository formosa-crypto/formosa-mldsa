#ifndef PQCLEAN_MLDSA65_AVX2_SIGN_H
#define PQCLEAN_MLDSA65_AVX2_SIGN_H
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include <stddef.h>
#include <stdint.h>

int PQCLEAN_MLDSA65_AVX2_crypto_sign_keypair(uint8_t *pk, uint8_t *sk, const uint8_t seed[SEEDBYTES]);

int PQCLEAN_MLDSA65_AVX2_crypto_sign_signature_ctx(uint8_t *sig, size_t *siglen,
        const uint8_t *m, size_t mlen,
        const uint8_t *ctx, size_t ctxlen,
        const uint8_t *sk,
        const uint8_t seed[RNDBYTES]);

int PQCLEAN_MLDSA65_AVX2_crypto_sign_verify_ctx(const uint8_t *sig, size_t siglen,
        const uint8_t *m, size_t mlen,
        const uint8_t *ctx, size_t ctxlen,
        const uint8_t *pk);

#endif
