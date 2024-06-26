#include "notrandombytes.c"

#include "test_macros.h"

#include "sign.h"
#include "fips202.h"

#ifndef TESTS
#define TESTS 1000
#endif

void PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed_jazz(uint8_t *pk, uint8_t *sk, uint8_t *sb);
void shake256_PUBLICKEYBYTES_SEEDBYTES(uint8_t *output, const uint8_t *input);

#include "sign_wrap.h"

void check_crypto_sign_signature() {
  size_t siglen = 0;
  size_t siglen_jazz = 0;
  size_t mlen = SEEDBYTES;
  size_t mlen_jazz = SEEDBYTES;
  uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES];
  uint8_t sig_jazz[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES];
  uint8_t m[SEEDBYTES];
  uint8_t m_jazz[SEEDBYTES];
  uint8_t pk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES];
  uint8_t sb[2 * SEEDBYTES + CRHBYTES];
  for(int t=0; t<TESTS; t++) {
    // Generates a keypair from random seed    
    fillarr(uint8_t, 2 * SEEDBYTES + CRHBYTES, sb);
    int status = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed(pk, sk, sb);
    if (status != 0) {
      printf("FAIL: crypto_sign_signature\n. Could not generate the key pair.");
      exit(1);
    }
    // Generates random message
    fillarrnu8(m, m_jazz, SEEDBYTES);
    // Sign the random message
    int r = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature(sig, &siglen, m, mlen, sk);
    int r_jazz = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature_jazz(sig_jazz, &siglen_jazz, m_jazz, mlen_jazz, sk);
    if (r != r_jazz) {
      printf("FAIL: crypto_sign_signature\n");
      exit(1);
    }
    eqarr(PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES, PRId8, sig, sig_jazz, "crypto_sign_signature");
  }
  printf("PASS: crypto_sign_signature\n");
}

void check_crypto_sign_verify() {
  size_t siglen = PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES;
  size_t mlen = SEEDBYTES;
  uint8_t m[SEEDBYTES];  
  uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES];
  uint8_t pk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES];
  uint8_t sb[2 * SEEDBYTES + CRHBYTES];  
  for(int t=0; t<TESTS; t++) {
    // Generates a keypair from random seed
    fillarr(uint8_t, 2 * SEEDBYTES + CRHBYTES, sb);
    int status = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed(pk, sk, sb);
    if (status != 0) {
      printf("FAIL: crypto_sign_verify\n. Could not generate the key pair.");
      exit(1);
    }
    // Generates random message
    fillarr(uint8_t, SEEDBYTES, m);
    // Sign the random message
    status = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature(sig, &siglen, m, mlen, sk);
    if (status != 0) {
      printf("FAIL: crypto_sign_verify\n. Could not generate the signature.");
      exit(1);
    }
    // Verify the maching between the signature and the message
    int r = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify(sig, PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES, m, SEEDBYTES, pk);
    if (r != 0) {
      printf("Could not verify signature with C code.");
      exit(1);
    }
    int r_jazz = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify_jazz(sig, PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES, m, SEEDBYTES, pk);
    if (r != r_jazz) {
      printf("FAIL: crypto_sign_verify\n");
      exit(1);
    }
  }
  printf("PASS: crypto_sign_verify\n");
}

int main ()
{
  //    check_outp_inp(shake256, shake256_PUBLICKEYBYTES_SEEDBYTES, "shake256_PUBLICKEYBYTES_SEEDBYTES");  
  //    check_pksk_pksksb(PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed_jazz, PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed, "crypto_sign_keypair_seed");
  //    check_crypto_sign_signature();    
    check_crypto_sign_verify();
    return 0;
}
