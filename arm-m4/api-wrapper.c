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

static int base16_decode(const uint8_t *in, const size_t in_len, uint8_t *out)
{
    if((in_len % 2) != 0 || !in || !out)
    {
        return(-1);
    }

    for(size_t i = 0;(i+1) < in_len;i+=2)
    {
        uint8_t byte1 = ASCIItoBase16[in[i]];
        if(byte1 == 0xFF)
        {
            return(-1);
        }
        uint8_t byte2 = ASCIItoBase16[in[i + 1]];
        if(byte2 == 0xFF)
        {
            return(-1);
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
        case 1: // Sign
            /*uint8_t signature[SIGNATURE_SIZE];
            *uint8_t ctx_m_rand[3] = {argv[1], argv[3], argv[5]};
            size_t ctxlen_mlen[2] = {atoi(argv[2]), atoi(argv[4])}

            ml_dsa_65_sign(signature, ctx_m_rand, argv[2], argv[6]);
            for (size_t i = 0; i < SIGNATURE_SIZE; i++) {
                printf("%x:", signature[i]);
            }*/
            break;
        case 2: // Verify
            break;
            /*uint8_t ctx_m[2] = {argv[2], argv[4]};
            size_t ctxlen_mlen[2] = {atoi(argv[3]), atoi(argv[5])}
            int result;

            result = ml_dsa_65_verify(argv[1], ctx_m, ctxlen_mlen, argv[6]);
            printf("%d", result);
            break;*/
    }

    return EXIT_SUCCESS;
}
