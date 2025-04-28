#include "version.h"

#include "notrandombytes.c"

#include "test_macros.h"

#include "sign.h"
#include "fips202.h"

#ifndef TESTS
#define TESTS 5
#endif

void JASMIN_VERSION(crypto_sign_keypair)(uint8_t *pk, uint8_t *sk);
void JASMIN_VERSION(crypto_sign_keypair_seed)(uint8_t *pk, uint8_t *sk, uint8_t *sb);

#include "sign_wrap.h"

void check_crypto_sign_keypair_seed() {
  uint8_t pk[PQCLEAN_VERSION(CRYPTO_PUBLICKEYBYTES)];
  uint8_t pk_jazz[PQCLEAN_VERSION(CRYPTO_PUBLICKEYBYTES)];
  uint8_t sk[PQCLEAN_VERSION(CRYPTO_SECRETKEYBYTES)];
  uint8_t sk_jazz[PQCLEAN_VERSION(CRYPTO_SECRETKEYBYTES)];
  uint8_t sb[SEEDBYTES];
  uint8_t sb_jazz[SEEDBYTES];
  for (int t=0; t<TESTS; t++) {
    fillarrnu8(sb, sb_jazz, SEEDBYTES);
    PQCLEAN_VERSION(crypto_sign_keypair_seed)(pk, sk, sb);
    JASMIN_VERSION(crypto_sign_keypair_seed)(pk_jazz, sk_jazz, sb_jazz);
    eqarr(PQCLEAN_VERSION(CRYPTO_PUBLICKEYBYTES), PRId8, pk, pk_jazz, "crypto_sign_keypair_seed: wrong pk");
    eqarr(PQCLEAN_VERSION(CRYPTO_SECRETKEYBYTES), PRId8, sk, sk_jazz, "crypto_sign_keypair_seed: wrong sk");
  }
  printf("PASS: crypto_sign_keypair_seed\n");
}

void check_crypto_sign_signature_ctx_seed() {
  size_t siglen = 0;
  size_t siglen_jazz = 0;
  size_t mlen = 453;
  size_t ctxlen = 239;
  uint8_t sig[PQCLEAN_VERSION(CRYPTO_BYTES)];
  uint8_t sig_jazz[PQCLEAN_VERSION(CRYPTO_BYTES)];
  uint8_t m[mlen];
  uint8_t m_jazz[mlen];
  uint8_t ctx[ctxlen];
  uint8_t ctx_jazz[ctxlen];
  uint8_t pk[PQCLEAN_VERSION(CRYPTO_PUBLICKEYBYTES)];
  uint8_t sk[PQCLEAN_VERSION(CRYPTO_SECRETKEYBYTES)];
  uint8_t sb[SEEDBYTES];
  uint8_t rand[RNDBYTES];
  uint8_t rand_jazz[RNDBYTES];
  for(int t=0; t<TESTS; t++) {
    // Generates a keypair from random seed
    fillarr(uint8_t, SEEDBYTES, sb);
    int status = PQCLEAN_VERSION(crypto_sign_keypair_seed)(pk, sk, sb);
    if (status != 0) {
      printf("FAIL: crypto_sign_signature_ctx_seed. Could not generate the key pair.");
      exit(1);
    }
    // Generates random message
    fillarrnu8(m, m_jazz, mlen);
    // Generates random context
    fillarrnu8(ctx, ctx_jazz, ctxlen);
    // Generates random randomness
    fillarrnu8(rand, rand_jazz, RNDBYTES);
    // Sign the random message
    int r = PQCLEAN_VERSION(crypto_sign_signature_ctx_seed)(sig, &siglen, m, mlen, ctx, ctxlen, sk, rand);
    if (r != 0) {
      printf("FAIL: crypto_sign_signature_ctx_seed. Could not generate the signature with C code.");
      exit(1);
    }
    int r_jazz = JASMIN_VERSION(crypto_sign_signature_ctx_seed)(sig_jazz, &siglen_jazz, m_jazz, mlen, ctx_jazz, ctxlen, sk, rand_jazz);
    if (r_jazz != 0) {
      printf("FAIL: crypto_sign_signature_ctx_seed. Could not generate the signature with jasmin code.");
      exit(1);
    }
    eqarr(PQCLEAN_VERSION(CRYPTO_BYTES), PRId8, sig, sig_jazz, "crypto_sign_signature_ctx_seed");
  }
  printf("PASS: crypto_sign_signature_ctx_seed\n");
}

void check_crypto_sign_keypair() {
  uint8_t pk[JASMIN_VERSION(CRYPTO_PUBLICKEYBYTES)];
  uint8_t sk[JASMIN_VERSION(CRYPTO_SECRETKEYBYTES)];
  size_t siglen = 0;
  uint8_t sig[JASMIN_VERSION(CRYPTO_BYTES)];

  for (int t=0; t<TESTS; t++) {

    uint8_t mlen;
    randombytes(&mlen, sizeof(mlen));
    uint8_t ctxlen;
    randombytes(&ctxlen, sizeof(ctxlen));

    uint8_t m[mlen];
    uint8_t ctx[ctxlen];

    JASMIN_VERSION(crypto_sign_keypair)(pk, sk);

    // Generates random message
    fillarr(uint8_t, mlen, m);
    // Generates random context
    fillarr(uint8_t, ctxlen, ctx);

    // Sign the random message
    int r_sign = PQCLEAN_VERSION(crypto_sign_signature_ctx)(sig, &siglen, m, mlen, ctx, ctxlen, sk);
    if (r_sign != 0) {
      printf("FAIL: crypto_sign_keypair. Could not generate the signature with C code.");
      exit(1);
    }

    // Verify the maching between the signature and the message
    int r_verify = PQCLEAN_VERSION(crypto_sign_verify_ctx)(sig, PQCLEAN_VERSION(CRYPTO_BYTES), m, mlen, ctx, ctxlen, pk);
    if (r_verify != 0) {
      printf("FAIL: crypto_sign_keypair. Could not verify signature with C code.");
      exit(1);
    }

  }
  printf("PASS: crypto_sign_keypair\n");
}

void check_crypto_sign_signature() {
  uint8_t pk[JASMIN_VERSION(CRYPTO_PUBLICKEYBYTES)];
  uint8_t sk[JASMIN_VERSION(CRYPTO_SECRETKEYBYTES)];
  size_t siglen = 0;
  uint8_t sig[JASMIN_VERSION(CRYPTO_BYTES)];

  for (int t=0; t<TESTS; t++) {

    uint8_t mlen;
    randombytes(&mlen, sizeof(mlen));
    uint8_t ctxlen;
    randombytes(&ctxlen, sizeof(ctxlen));

    uint8_t m[mlen];
    uint8_t ctx[ctxlen];

    PQCLEAN_VERSION(crypto_sign_keypair)(pk, sk);

    // Generates random message
    fillarr(uint8_t, mlen, m);
    // Generates random context
    fillarr(uint8_t, ctxlen, ctx);

    // Sign the random message
    int r_signature = JASMIN_VERSION(crypto_sign_signature_ctx)(sig, &siglen, m, mlen, ctx, ctxlen, sk);
    if (r_signature != 0) {
      printf("FAIL: crypto_sign_signature. Could not generate the signature with Jasmin code.");
      exit(1);
    }

    // Verify the maching between the signature and the message
    int r_verify = PQCLEAN_VERSION(crypto_sign_verify_ctx)(sig, PQCLEAN_VERSION(CRYPTO_BYTES), m, mlen, ctx, ctxlen, pk);
    if (r_verify != 0) {
      printf("FAIL: crypto_sign_signature. Could not verify signature with C code.");
      exit(1);
    }

  }
  printf("PASS: crypto_sign_signature\n");
}

void check_crypto_sign_verify() {
  uint8_t pk[JASMIN_VERSION(CRYPTO_PUBLICKEYBYTES)];
  uint8_t sk[JASMIN_VERSION(CRYPTO_SECRETKEYBYTES)];
  size_t siglen = 0;
  uint8_t sig[JASMIN_VERSION(CRYPTO_BYTES)];

  for (int t=0; t<TESTS; t++) {

    uint8_t mlen;
    randombytes(&mlen, sizeof(mlen));
    uint8_t ctxlen;
    randombytes(&ctxlen, sizeof(ctxlen));

    uint8_t m[mlen];
    uint8_t ctx[ctxlen];

    PQCLEAN_VERSION(crypto_sign_keypair)(pk, sk);

    // Generates random message
    fillarr(uint8_t, mlen, m);
    // Generates random context
    fillarr(uint8_t, ctxlen, ctx);

    // Sign the random message
    int r_signature = PQCLEAN_VERSION(crypto_sign_signature_ctx)(sig, &siglen, m, mlen, ctx, ctxlen, sk);
    if (r_signature != 0) {
      printf("FAIL: crypto_sign_verify. Could not generate the signature with C code.");
      exit(1);
    }

    // Verify the maching between the signature and the message
    int r_verify = JASMIN_VERSION(crypto_sign_verify_ctx)(sig, PQCLEAN_VERSION(CRYPTO_BYTES), m, mlen, ctx, ctxlen, pk);
    if (r_verify != 0) {
      printf("FAIL: crypto_sign_verify. Could not verify signature with Jasmin code.");
      exit(1);
    }

  }
  printf("PASS: crypto_sign_verify\n");
}

int main ()
{
  // Check that output match between C and Jasmin implementation with controled randomness
  check_crypto_sign_keypair_seed();
  check_crypto_sign_signature_ctx_seed();

  // Check inter-operability between C and Jasmin implementation without controled randomness
  check_crypto_sign_keypair();
  check_crypto_sign_signature();
  check_crypto_sign_verify();

  return 0;
}
