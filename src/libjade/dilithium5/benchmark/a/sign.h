#ifndef SIGN_H
#define SIGN_H

#include <stddef.h>
#include <stdint.h>
#include "params.h"
#include "api.h"
#include "polyvec.h"
#include "poly.h"

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair(uint8_t *pk, uint8_t *sk);

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed(uint8_t *pk, uint8_t *sk, uint8_t* seedbuf);

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature(uint8_t *sig, size_t *siglen,
                          const uint8_t *m, size_t mlen,
                          const uint8_t *sk);

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign(uint8_t *sm, size_t *smlen,
                const uint8_t *m, size_t mlen,
                const uint8_t *sk);

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify(const uint8_t *sig, size_t siglen,
                       const uint8_t *m, size_t mlen,
                       const uint8_t *pk);

int PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_open(uint8_t *m, size_t *mlen,
                     const uint8_t *sm, size_t smlen,
                     const uint8_t *pk);
#endif
