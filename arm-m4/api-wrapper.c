#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "api.h"

const uint8_t ASCIItoBase16[128] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x0,  0x1,  0x2,  0x3,  0x4,  0x5,  0x6,  0x7,
  0x8,  0x9,  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xA,  0xB,  0xC,  0xD,  0xE,  0xF,  0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xA,  0xB,  0xC,  0xD,  0xE,  0xF,  0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

size_t base16_decode_len(const size_t in_len)
{
    return in_len >> 1;
}

static int base16_decode(const uint8_t *in, const size_t in_len, uint8_t *out)
{
    if((in_len % 2) != 0 || !in || !out)
    {
        return -1;
    }

    for(size_t i = 0;(i+1) < in_len;i+=2)
    {
        uint8_t byte1 = ASCIItoBase16[in[i]];
        if(byte1 == 0xFF)
        {
            return -1;
        }
        uint8_t byte2 = ASCIItoBase16[in[i + 1]];
        if(byte2 == 0xFF)
        {
            return -1;
        }
        *out++ = (uint8_t)(byte1 << 4) | byte2;
    }
    return(0);
}

int main(int argc, char *argv[])
{
    int operation = atoi(argv[1]);
    switch(operation) {
        case 0: // Keygen
        {
            uint8_t verification_key[VERIFICATION_KEY_SIZE];
            uint8_t signing_key[SIGNING_KEY_SIZE];
            uint8_t randomness[32];

            int result = base16_decode(argv[2], 64, randomness);
            assert(result == 0);

            ml_dsa_65_keygen(verification_key, signing_key, randomness);

            for (size_t i = 0; i < VERIFICATION_KEY_SIZE; i++) {
                printf("%02x", verification_key[i]);
            }
            printf(":");

            for (size_t i = 0; i < SIGNING_KEY_SIZE; i++) {
                printf("%02x", signing_key[i]);
            }

            break;
        }
        case 1: // Sign
        {
            uint8_t signature[SIGNATURE_SIZE];
            uint8_t* ctx_m_rand[3];
            size_t ctxlen_mlen[2];

            uint8_t context[255];
            size_t encoded_context_len, context_len;

            uint8_t* message;
            size_t encoded_message_len, message_len;

            uint8_t randomness[32];

            uint8_t signing_key[SIGNING_KEY_SIZE];

            // Decode the context
            encoded_context_len = atoi(argv[2]);
            context_len = base16_decode_len(encoded_context_len);

            int result = base16_decode(argv[3], encoded_context_len, context);
            assert(result == 0);

            ctx_m_rand[0] = context;
            ctxlen_mlen[0] = context_len;

            // Message
            encoded_message_len = atoi(argv[4]);
            message_len = base16_decode_len(encoded_message_len);

            message = malloc(message_len);

            result = base16_decode(argv[5], encoded_message_len, message);
            assert(result == 0);

            ctx_m_rand[1] = message;
            ctxlen_mlen[1] = message_len;

            // Next, the randomness
            result = base16_decode(argv[6], 64, randomness);
            assert(result == 0);

            ctx_m_rand[2] = randomness;

            // Finally, the signing key
            result = base16_decode(argv[7], SIGNING_KEY_SIZE * 2, signing_key);
            assert(result == 0);

            result = ml_dsa_65_sign(signature, ctx_m_rand, ctxlen_mlen, signing_key);
            assert(result == 0);

            for (size_t i = 0; i < SIGNATURE_SIZE; i++) {
                printf("%02x", signature[i]);
            }
            break;
        }
        case 2: // Verify
        {
            uint8_t signature[SIGNATURE_SIZE];
            uint8_t* ctx_m[2];
            size_t ctxlen_mlen[2];

            uint8_t context[255];
            size_t encoded_context_len, context_len;

            uint8_t* message;
            size_t encoded_message_len, message_len;

            uint8_t verification_key[VERIFICATION_KEY_SIZE];

            // Decode the context
            encoded_context_len = atoi(argv[2]);
            context_len = base16_decode_len(encoded_context_len);

            int result = base16_decode(argv[3], encoded_context_len, context);
            assert(result == 0);

            ctx_m[0] = context;
            ctxlen_mlen[0] = context_len;

            // Message
            encoded_message_len = atoi(argv[4]);
            message_len = base16_decode_len(encoded_message_len);

            message = malloc(message_len);

            result = base16_decode(argv[5], encoded_message_len, message);
            assert(result == 0);

            ctx_m[1] = message;
            ctxlen_mlen[1] = message_len;

            // Finally, the signature
            result = base16_decode(argv[6], SIGNATURE_SIZE * 2, signature);
            assert(result == 0);

            // Finally, the verification key
            result = base16_decode(argv[7], VERIFICATION_KEY_SIZE * 2, verification_key);
            assert(result == 0);

            result = ml_dsa_65_verify(signature, ctx_m, ctxlen_mlen, verification_key);
            printf("%d", result);
            break;
        }
    }

    return EXIT_SUCCESS;
}
