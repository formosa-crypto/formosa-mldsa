#ifndef PQCLEAN_MLDSA65_AVX2_API_H
#define PQCLEAN_MLDSA65_AVX2_API_H

#include <stddef.h>
#include <stdint.h>

#define PQCLEAN_MLDSA65_AVX2_CRYPTO_PUBLICKEYBYTES 1952
#define PQCLEAN_MLDSA65_AVX2_CRYPTO_SECRETKEYBYTES 4032
#define PQCLEAN_MLDSA65_AVX2_CRYPTO_BYTES 3309
#define PQCLEAN_MLDSA65_AVX2_CRYPTO_ALGNAME "ML-DSA-65"

int PQCLEAN_MLDSA65_AVX2_crypto_sign_keypair(uint8_t *pk, uint8_t *sk, const uint8_t seed[32]);

int PQCLEAN_MLDSA65_AVX2_crypto_sign_signature_ctx(uint8_t *sig, size_t *siglen,
        const uint8_t *m, size_t mlen,
        const uint8_t *ctx, size_t ctxlen,
        const uint8_t *sk,
        const uint8_t seed[32]);

int PQCLEAN_MLDSA65_AVX2_crypto_sign_verify_ctx(const uint8_t *sig, size_t siglen,
        const uint8_t *m, size_t mlen,
        const uint8_t *ctx, size_t ctxlen,
        const uint8_t *pk);
#endif
