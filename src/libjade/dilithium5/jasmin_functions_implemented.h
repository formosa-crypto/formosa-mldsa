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

/* reduce */

#define montgomery_reduce_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz

#define reduce32_jazz 
#define PQCLEAN_DILITHIUM5_CLEAN_reduce32 PQCLEAN_DILITHIUM5_CLEAN_reduce32_jazz

#define caddq_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_caddq PQCLEAN_DILITHIUM5_CLEAN_caddq_jazz

#define freeze_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_freeze PQCLEAN_DILITHIUM5_CLEAN_freeze_jazz

/* ntt */

#define ntt_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_ntt PQCLEAN_DILITHIUM5_CLEAN_ntt_jazz

#define invntt_tomont_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_ntt PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont_jazz

/* rouding */

#define power2round_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_power2round PQCLEAN_DILITHIUM5_CLEAN_power2round_jazz

#define decompose_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_decompose PQCLEAN_DILITHIUM5_CLEAN_decompose_jazz

//make_hint
//use_hint


/* poly */

//poly_reduce
//poly_caddq
//poly_add
//poly_sub
//poly_shiftl
//poly_ntt
//poly_invntt_tomont
//poly_pointwise_montgomery
//poly_power2round
//poly_decompose
//poly_make_hint
//poly_use_hint
//poly_chknorm
//rej_uniform !!!
//poly_uniform
//rej_eta !!!
//poly_uniform_eta
//poly_uniform_gamma1
//poly_challenge
//polyeta_pack
//polyeta_unpack
//polyt1_pack
//polyt1_unpack
//polyt0_pack
//polyt0_unpack
//polyz_pack
//polyz_unpack
//polyw1_pack

#endif

#endif
