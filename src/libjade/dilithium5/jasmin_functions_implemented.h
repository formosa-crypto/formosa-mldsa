#ifndef JASMIN_FUNCTIONS_IMPLEMENTED_H
#define JASMIN_FUNCTIONS_IMPLEMENTED_H


/*
#define XXX_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_XXX PQCLEAN_DILITHIUM5_CLEAN_XXX_jazz
*/


#ifdef JAZZ
// if JAZZ compilation is defined then the 'full compilation' mode is active,
// which means that in the libdilithium5_clean.a the C versions of the functions
// will not be present

// reduce 
#define montgomery_reduce_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz

#define reduce32_jazz 
#define PQCLEAN_DILITHIUM5_CLEAN_reduce32 PQCLEAN_DILITHIUM5_CLEAN_reduce32_jazz

#define caddq_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_caddq PQCLEAN_DILITHIUM5_CLEAN_caddq_jazz

#define freeze_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_freeze PQCLEAN_DILITHIUM5_CLEAN_freeze_jazz

// ntt  
#define ntt_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_ntt PQCLEAN_DILITHIUM5_CLEAN_ntt_jazz

#define invntt_tomont_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_ntt PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont_jazz


#endif

#endif
