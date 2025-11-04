#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "api.h"

int main(int argc, char *argv[]) {
  int result;
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

    result = 0;

    break;
  }
  case 1: // Sign
  {
    // Inputs
    size_t context_len;
    uint8_t *context;

    size_t message_len;
    uint8_t *message;

    uint8_t randomness[32];

    uint8_t signing_key[SIGNING_KEY_SIZE];

    // Outputs
    uint8_t signature[SIGNATURE_SIZE];

    // Get the context
    int num_bytes = read(0, &context_len, sizeof(context_len));
    assert(num_bytes == sizeof(context_len));

    context = malloc(context_len);

    num_bytes = read(0, context, context_len);
    assert(num_bytes == context_len);

    // Get the message
    num_bytes = read(0, &message_len, sizeof(message_len));
    assert(num_bytes == sizeof(message_len));

    message = malloc(message_len);

    num_bytes = read(0, message, message_len);
    assert(num_bytes == message_len);

    // Next, the randomness
    num_bytes = read(0, randomness, 32);
    assert(num_bytes == 32);

    // Finally, the signing key
    num_bytes = read(0, signing_key, SIGNING_KEY_SIZE);
    assert(num_bytes == SIGNING_KEY_SIZE);

    const uint8_t *ctx_m_rand[3] = {context, message, randomness};
    const size_t ctxlen_mlen[2] = {context_len, message_len};
    result = SIGN(signature, ctx_m_rand, ctxlen_mlen, signing_key);

    num_bytes = write(1, signature, SIGNATURE_SIZE);
    assert(num_bytes == SIGNATURE_SIZE);

    break;
  }
  case 2: // Verify
  {
    // Inputs
    size_t context_len;
    uint8_t *context;

    size_t message_len;
    uint8_t *message;

    uint8_t signature[SIGNATURE_SIZE];

    uint8_t verification_key[VERIFICATION_KEY_SIZE];

    // Get the context
    int num_bytes = read(0, &context_len, sizeof(context_len));
    assert(num_bytes == sizeof(context_len));

    context = malloc(context_len);

    num_bytes = read(0, context, context_len);
    assert(num_bytes == context_len);

    // Get the message
    num_bytes = read(0, &message_len, 4);
    assert(num_bytes == 4);

    message = malloc(message_len);

    num_bytes = read(0, message, message_len);
    assert(num_bytes == message_len);

    // Next, the signature
    num_bytes = read(0, signature, SIGNATURE_SIZE);
    assert(num_bytes == SIGNATURE_SIZE);

    // Finally, the verification key
    num_bytes = read(0, verification_key, VERIFICATION_KEY_SIZE);
    assert(num_bytes == VERIFICATION_KEY_SIZE);

    const uint8_t *ctx_m[2] = {context, message};
    const size_t ctxlen_mlen[2] = {context_len, message_len};
    result = VERIFY(signature, ctx_m, ctxlen_mlen, verification_key);

    break;
  }
  }

  return result;
}
