#include <stdint.h>

#define Q 8380417

/*************************************************
* Name:        PQCLEAN_DILITHIUM5_CLEAN_caddq
*
* Description: Add Q if input coefficient is negative.
*
* Arguments:   - int32_t: finite field element a
*
* Returns r.
**************************************************/
int32_t caddq(int32_t a) {
    a += (a >> 31) & Q;
    return a;
}

