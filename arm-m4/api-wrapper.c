#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "api.h"

int main(int argc, char *argv[])
{
    if (strncmp(argv[1], "keygen", 6) == 0) {
        uint8_t verification_key[VERIFICATION_KEY_SIZE];
        uint8_t signing_key[SIGNING_KEY_SIZE];
        ml_dsa_65_keygen(verification_key, signing_key, (const uint8_t*)argv[2]);
        for (size_t i = 0; i < VERIFICATION_KEY_SIZE; i++) {
            printf("%x:", verification_key[i]);
        }
        printf(",");
        for (size_t i = 0; i < SIGNING_KEY_SIZE; i++) {
            printf("%x:", signing_key[i]);
        }
    }
        /*case "keygen":
            break;
        case "sign":
            uint8_t signature[SIGNATURE_SIZE];
            *uint8_t ctx_m_rand[3] = {argv[1], argv[3], argv[5]};
            size_t ctxlen_mlen[2] = {atoi(argv[2]), atoi(argv[4])}

            ml_dsa_65_sign(signature, ctx_m_rand, argv[2], argv[6]);
            for (size_t i = 0; i < SIGNATURE_SIZE; i++) {
                printf("%x:", signature[i]);
            }
            break;
        case "verify":
            *uint8_t ctx_m[2] = {argv[2], argv[4]};
            size_t ctxlen_mlen[2] = {atoi(argv[3]), atoi(argv[5])}
            int result;

            result = ml_dsa_65_verify(argv[1], ctx_m, ctxlen_mlen, argv[6]);
            printf("%d", result);
            break;
    }*/

    return EXIT_SUCCESS;
}
