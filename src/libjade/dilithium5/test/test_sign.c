#include "notrandombytes.c"

#include "test_macros.h"

#include "sign.h"
#include "fips202.h"

#ifndef TESTS
#define TESTS 1000
#endif

void PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed_jazz(uint8_t *pk, uint8_t *sk, uint8_t *sb);
void shake256_PUBLICKEYBYTES_SEEDBYTES(uint8_t *output, const uint8_t *input);
				       
int main ()
{
    check_outp_inp(shake256, shake256_PUBLICKEYBYTES_SEEDBYTES, "shake256_PUBLICKEYBYTES_SEEDBYTES");  
    check_pksk_pksksb(PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed_jazz, PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed, "crypto_sign_keypair_seed");
    return 0;
}
