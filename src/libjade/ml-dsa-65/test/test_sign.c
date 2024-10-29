#include "notrandombytes.c"

#include "test_macros.h"

#include "sign.h"
#include "fips202.h"

#ifndef TESTS
#define TESTS 5
#endif

void JASMIN_MLDSA65_crypto_sign_keypair_seed(uint8_t *pk, uint8_t *sk, uint8_t *sb);
void shake256_PUBLICKEYBYTES_SEEDBYTES(uint8_t *output, const uint8_t *input);

#include "sign_wrap.h"

void check_crypto_sign_keypair_seed() {
  uint8_t pk[PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t pk_jazz[PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[PQCLEAN_MLDSA65_CLEAN_CRYPTO_SECRETKEYBYTES];
  uint8_t sk_jazz[PQCLEAN_MLDSA65_CLEAN_CRYPTO_SECRETKEYBYTES];
  uint8_t sb[2 * SEEDBYTES + CRHBYTES];
  uint8_t sb_jazz[2 * SEEDBYTES + CRHBYTES];
  for (int t=0; t<TESTS; t++) {
    fillarrnu8(sb, sb_jazz, 2 * SEEDBYTES + CRHBYTES);
    PQCLEAN_MLDSA65_CLEAN_crypto_sign_keypair_seed(pk, sk, sb);
    JASMIN_MLDSA65_crypto_sign_keypair_seed(pk_jazz, sk_jazz, sb_jazz);
    eqarr(PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES, PRId8, pk, pk_jazz, "crypto_sign_keypair_seed: wrong pk");
    eqarr(PQCLEAN_MLDSA65_CLEAN_CRYPTO_SECRETKEYBYTES, PRId8, sk, sk_jazz, "crypto_sign_keypair_seed: wrong sk");
  }
  printf("PASS: crypto_sign_keypair_seed\n");
}

void check_shake256_PUBLICKEYBYTES_SEEDBYTES() {
  uint8_t outp[SEEDBYTES];
  uint8_t outp_jazz[SEEDBYTES];
  uint8_t inp[PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t inp_jazz[PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES];
  for (int t=0; t<TESTS; t++) {
    fillarrnu8(inp, inp_jazz, PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES);
    shake256(outp, SEEDBYTES, inp, PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES);
    shake256_PUBLICKEYBYTES_SEEDBYTES(outp_jazz, inp_jazz);
    eqarr(SEEDBYTES, PRId8, outp, outp_jazz, "shake256_PUBLICKEYBYTES_SEEDBYTES");
  }
  printf("PASS: shake256_PUBLICKEYBYTES_SEEDBYTES\n");
}

void check_crypto_sign_signature_ctx() {
  size_t siglen = 0;
  size_t siglen_jazz = 0;
  size_t mlen = 369;
  size_t ctxlen = 0;
  uint8_t sig[PQCLEAN_MLDSA65_CLEAN_CRYPTO_BYTES];
  uint8_t sig_jazz[PQCLEAN_MLDSA65_CLEAN_CRYPTO_BYTES];
  uint8_t m[mlen];
  uint8_t m_jazz[mlen];
  uint8_t ctx[ctxlen];
  uint8_t ctx_jazz[ctxlen];
  uint8_t pk[PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[PQCLEAN_MLDSA65_CLEAN_CRYPTO_SECRETKEYBYTES];
  uint8_t sb[2 * SEEDBYTES + CRHBYTES];
  for(int t=0; t<TESTS; t++) {
    // Generates a keypair from random seed    
    fillarr(uint8_t, 2 * SEEDBYTES + CRHBYTES, sb);
    int status = PQCLEAN_MLDSA65_CLEAN_crypto_sign_keypair_seed(pk, sk, sb);
    if (status != 0) {
      printf("FAIL: crypto_sign_signature\n. Could not generate the key pair.");
      exit(1);
    }
    // Generates random message
    fillarrnu8(m, m_jazz, mlen);
    // Sign the random message
    int r = PQCLEAN_MLDSA65_CLEAN_crypto_sign_signature_ctx(sig, &siglen, m, mlen, ctx, ctxlen, sk);
    int r_jazz = JASMIN_MLDSA65_crypto_sign_signature_ctx(sig_jazz, &siglen_jazz, m_jazz, mlen, ctx_jazz, ctxlen, sk);
    if (r != r_jazz) {
      printf("FAIL: crypto_sign_signature_ctx\n");
      exit(1);
    }
    eqarr(PQCLEAN_MLDSA65_CLEAN_CRYPTO_BYTES, PRId8, sig, sig_jazz, "crypto_sign_signature_ctx");
  }
  printf("PASS: crypto_sign_signature\n");
}

void check_crypto_sign_verify_ctx() {
  size_t siglen = PQCLEAN_MLDSA65_CLEAN_CRYPTO_BYTES;
  size_t mlen = 67;
  uint8_t m[mlen];
  size_t ctxlen = 823;
  uint8_t ctx[ctxlen];
  uint8_t sig[PQCLEAN_MLDSA65_CLEAN_CRYPTO_BYTES];
  uint8_t pk[PQCLEAN_MLDSA65_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[PQCLEAN_MLDSA65_CLEAN_CRYPTO_SECRETKEYBYTES];
  uint8_t sb[2 * SEEDBYTES + CRHBYTES];  
  for(int t=0; t<TESTS; t++) {
    // Generates a keypair from random seed
    fillarr(uint8_t, 2 * SEEDBYTES + CRHBYTES, sb);
    int status = PQCLEAN_MLDSA65_CLEAN_crypto_sign_keypair_seed(pk, sk, sb);
    if (status != 0) {
      printf("FAIL: crypto_sign_verify\n. Could not generate the key pair.");
      exit(1);
    }
    // Generates random message
    fillarr(uint8_t, mlen, m);
    // Sign the random message
    status = PQCLEAN_MLDSA65_CLEAN_crypto_sign_signature_ctx(sig, &siglen, m, mlen, ctx, ctxlen, sk);
    if (status != 0) {
      printf("FAIL: crypto_sign_verify\n. Could not generate the signature.");
      exit(1);
    }
    // Verify the maching between the signature and the message
    int r = PQCLEAN_MLDSA65_CLEAN_crypto_sign_verify_ctx(sig, PQCLEAN_MLDSA65_CLEAN_CRYPTO_BYTES, m, mlen, ctx, ctxlen, pk);
    if (r != 0) {
      printf("Could not verify signature with C code.");
      exit(1);
    }
    int r_jazz = JASMIN_MLDSA65_crypto_sign_verify_ctx(sig, PQCLEAN_MLDSA65_CLEAN_CRYPTO_BYTES, m, mlen, ctx, ctxlen, pk);
    if (r != r_jazz) {
      printf("FAIL: crypto_sign_verify\n");
      exit(1);
    }
  }
  printf("PASS: crypto_sign_verify\n");
}

int main ()
{
  check_shake256_PUBLICKEYBYTES_SEEDBYTES();
  check_crypto_sign_keypair_seed();
  check_crypto_sign_signature_ctx();
  check_crypto_sign_verify_ctx();

  return 0;
}
