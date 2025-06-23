#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "api.h"

int main(int argc, char *argv[]) {
  int operation = atoi(argv[1]);
  switch (operation) {
  case 0: // Keygen
  {
    // Inputs, read in binary from stdin
    uint8_t randomness[32];

    // Outputs, written in binary to stdout
    uint8_t verification_key[VERIFICATION_KEY_SIZE];
    uint8_t signing_key[SIGNING_KEY_SIZE];

    int num_bytes = read(0, randomness, 32);
    assert(num_bytes == 32);

    KEYGEN(verification_key, signing_key, randomness);

    num_bytes = write(1, verification_key, VERIFICATION_KEY_SIZE);
    assert(num_bytes == VERIFICATION_KEY_SIZE);

    num_bytes = write(1, signing_key, SIGNING_KEY_SIZE);
    assert(num_bytes == SIGNING_KEY_SIZE);

    break;
  }
  case 1: // Sign
  {
    // Inputs
    uint8_t context_len;
    uint8_t* context;

    size_t message_len;
    uint8_t* message;

    uint8_t *ctx_m_rand[3];
    size_t ctxlen_mlen[2];

    uint8_t randomness[32];

    uint8_t signing_key[SIGNING_KEY_SIZE];

    // Outputs
    uint8_t signature[SIGNATURE_SIZE];

    // Get the context
    int num_bytes = read(0, &context_len, 1);
    assert(num_bytes == 1);

    context = malloc(context_len);

    num_bytes = read(0, context, context_len);
    assert(num_bytes == context_len);

    ctx_m_rand[0] = context;
    ctxlen_mlen[0] = context_len;

    // Get the message
    num_bytes = read(0, &message_len, 4);
    assert(num_bytes == 4);

    message = malloc(message_len);

    num_bytes = read(0, message, message_len);
    assert(num_bytes == message_len);

    ctx_m_rand[1] = message;
    ctxlen_mlen[1] = message_len;

    // Next, the randomness
    num_bytes = read(0, randomness, 32);
    assert(num_bytes == 32);

    ctx_m_rand[2] = randomness;

    // Finally, the signing key
    num_bytes = read(0, signing_key, SIGNING_KEY_SIZE);
    assert(num_bytes == SIGNING_KEY_SIZE);

    int result = SIGN(signature, ctx_m_rand, ctxlen_mlen, signing_key);
    assert(result == 0);

    num_bytes = write(1, signature, SIGNATURE_SIZE);
    assert(num_bytes == SIGNATURE_SIZE);

    break;
  }
  case 2: // Verify
  {
    // Inputs
    uint8_t context_len;
    uint8_t* context;

    size_t message_len;
    uint8_t* message;

    uint8_t *ctx_m[2];
    size_t ctxlen_mlen[2];

    uint8_t signature[SIGNATURE_SIZE];

    uint8_t verification_key[VERIFICATION_KEY_SIZE];

    // Get the context
    int num_bytes = read(0, &context_len, 1);
    assert(num_bytes == 1);

    context = malloc(context_len);

    num_bytes = read(0, context, context_len);
    assert(num_bytes == context_len);

    ctx_m[0] = context;
    ctxlen_mlen[0] = context_len;

    // Get the message
    num_bytes = read(0, &message_len, 4);
    assert(num_bytes == 4);

    message = malloc(message_len);

    num_bytes = read(0, message, message_len);
    assert(num_bytes == message_len);

    ctx_m[1] = message;
    ctxlen_mlen[1] = message_len;

    // Next, the signature
    num_bytes = read(0, signature, SIGNATURE_SIZE);
    assert(num_bytes == SIGNATURE_SIZE);

    // Finally, the verification key
    num_bytes = read(0, verification_key, VERIFICATION_KEY_SIZE);
    assert(num_bytes == VERIFICATION_KEY_SIZE);

    int8_t result = VERIFY(signature, ctx_m, ctxlen_mlen, verification_key);

    num_bytes = write(1, &result, 1);
    assert(num_bytes == 1);

    break;
  }
  }

  return EXIT_SUCCESS;
}
