#include "notrandombytes.c"

#include "time.h"
#include "test_macros.h"
#include "sign.h"

#ifndef RUNS
#define RUNS 10000
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 10000
#endif

int main () {
  uint8_t pk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_SECRETKEYBYTES];
  uint8_t sb[2 * SEEDBYTES + CRHBYTES];
  uint8_t sig[PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES];
  uint8_t m[MESSAGE_SIZE];
  size_t mlen = MESSAGE_SIZE;
  size_t siglen = 0;
  
  clock_t start_time, end_time;
  double time_taken;

  start_time = clock();
  for (int t=0; t<RUNS; t++) {
    fillarr(uint8_t, 2 * SEEDBYTES + CRHBYTES, sb);
    PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed(pk, sk, sb);
  }  
  end_time = clock();
  
  time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC / RUNS;
  printf("Keygen execution time: %f seconds\n", time_taken);
  
  start_time = clock();
  // Retrieves the last generated key pair to sign messages
  for (int t=0; t<RUNS; t++) {  
    // Generates random message
    fillarr(uint8_t, MESSAGE_SIZE, m);
    // Sign the random message
    int r = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature(sig, &siglen, m, mlen, sk);
    if (r != 0) {
      printf("Signature failed\n");
      exit(1);
    }
  }
  end_time = clock();
  
  time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC / RUNS;
  printf("Signature execution time: %f seconds\n", time_taken);

  start_time = clock();
  // Retrieves the last signature (TODO : do better)
  for (int t=0; t<RUNS; t++) {
    int r = PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify(sig, PQCLEAN_DILITHIUM5_CLEAN_CRYPTO_BYTES, m, MESSAGE_SIZE, pk);
    if (r != 0) {
      printf("Verification failed\n");
      exit(1);
    }
  }
  end_time = clock();
  
  time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC / RUNS;
  printf("Verification execution time: %f seconds\n", time_taken);

  return 0;
}
