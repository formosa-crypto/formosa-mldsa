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
#define PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont PQCLEAN_DILITHIUM5_CLEAN_invntt_tomont_jazz

// /////////////////////////////////////////////////////////////////////////////
// the following macros were generated using
// $ dilithium-arm/src/libjade/dilithium5$ for file in ntt.o rounding.o poly.o polyvec.o packing.o sign.o; do echo "// /////////////////////////////////////////////////////////////////////////////"; echo "// $file"; nm $file | grep " T " | cut -d' ' -f3 | while read str; do echo "#define ${str/PQCLEAN_DILITHIUM5_CLEAN_/}_jazz"; echo "#define $str ${str}_jazz"; echo ""; done; done

// /////////////////////////////////////////////////////////////////////////////
// rounding.o
#define decompose_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_decompose PQCLEAN_DILITHIUM5_CLEAN_decompose_jazz

#define power2round_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_power2round PQCLEAN_DILITHIUM5_CLEAN_power2round_jazz

#define make_hint_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_make_hint PQCLEAN_DILITHIUM5_CLEAN_make_hint_jazz

#define use_hint_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_use_hint PQCLEAN_DILITHIUM5_CLEAN_use_hint_jazz

// /////////////////////////////////////////////////////////////////////////////
// poly.o
#define poly_add_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_add PQCLEAN_DILITHIUM5_CLEAN_poly_add_jazz

#define poly_caddq_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_caddq PQCLEAN_DILITHIUM5_CLEAN_poly_caddq_jazz

#define poly_challenge_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_challenge PQCLEAN_DILITHIUM5_CLEAN_poly_challenge_jazz
#endif

#if 0
#define poly_chknorm_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_chknorm PQCLEAN_DILITHIUM5_CLEAN_poly_chknorm_jazz
#endif

#if 0
#define poly_decompose_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_decompose PQCLEAN_DILITHIUM5_CLEAN_poly_decompose_jazz

#if 0
#define polyeta_pack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyeta_pack PQCLEAN_DILITHIUM5_CLEAN_polyeta_pack_jazz

#define polyeta_unpack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyeta_unpack PQCLEAN_DILITHIUM5_CLEAN_polyeta_unpack_jazz

#define poly_invntt_tomont_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_invntt_tomont PQCLEAN_DILITHIUM5_CLEAN_poly_invntt_tomont_jazz

#define poly_make_hint_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_make_hint PQCLEAN_DILITHIUM5_CLEAN_poly_make_hint_jazz

#define poly_ntt_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_ntt PQCLEAN_DILITHIUM5_CLEAN_poly_ntt_jazz

#define poly_pointwise_montgomery_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_pointwise_montgomery PQCLEAN_DILITHIUM5_CLEAN_poly_pointwise_montgomery_jazz

#define poly_power2round_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_power2round PQCLEAN_DILITHIUM5_CLEAN_poly_power2round_jazz
#endif 

#define poly_reduce_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_reduce PQCLEAN_DILITHIUM5_CLEAN_poly_reduce_jazz

#if 0
#define poly_shiftl_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_shiftl PQCLEAN_DILITHIUM5_CLEAN_poly_shiftl_jazz

#define poly_sub_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_sub PQCLEAN_DILITHIUM5_CLEAN_poly_sub_jazz

#define polyt0_pack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyt0_pack PQCLEAN_DILITHIUM5_CLEAN_polyt0_pack_jazz

#define polyt0_unpack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyt0_unpack PQCLEAN_DILITHIUM5_CLEAN_polyt0_unpack_jazz

#define polyt1_pack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyt1_pack PQCLEAN_DILITHIUM5_CLEAN_polyt1_pack_jazz

#define polyt1_unpack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyt1_unpack PQCLEAN_DILITHIUM5_CLEAN_polyt1_unpack_jazz

#define poly_uniform_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_uniform PQCLEAN_DILITHIUM5_CLEAN_poly_uniform_jazz

#define poly_uniform_eta_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_uniform_eta PQCLEAN_DILITHIUM5_CLEAN_poly_uniform_eta_jazz

#define poly_uniform_gamma1_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_uniform_gamma1 PQCLEAN_DILITHIUM5_CLEAN_poly_uniform_gamma1_jazz

#define poly_use_hint_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_poly_use_hint PQCLEAN_DILITHIUM5_CLEAN_poly_use_hint_jazz

#define polyw1_pack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyw1_pack PQCLEAN_DILITHIUM5_CLEAN_polyw1_pack_jazz

#define polyz_pack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyz_pack PQCLEAN_DILITHIUM5_CLEAN_polyz_pack_jazz

#define polyz_unpack_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyz_unpack PQCLEAN_DILITHIUM5_CLEAN_polyz_unpack_jazz
#endif

// /////////////////////////////////////////////////////////////////////////////
// polyvec.o
#if 0
#define polyveck_add_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_add PQCLEAN_DILITHIUM5_CLEAN_polyveck_add_jazz

#define polyveck_caddq_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_caddq PQCLEAN_DILITHIUM5_CLEAN_polyveck_caddq_jazz

#define polyveck_chknorm_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_chknorm PQCLEAN_DILITHIUM5_CLEAN_polyveck_chknorm_jazz

#define polyveck_decompose_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_decompose PQCLEAN_DILITHIUM5_CLEAN_polyveck_decompose_jazz

#define polyveck_invntt_tomont_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_invntt_tomont PQCLEAN_DILITHIUM5_CLEAN_polyveck_invntt_tomont_jazz

#define polyveck_make_hint_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_make_hint PQCLEAN_DILITHIUM5_CLEAN_polyveck_make_hint_jazz

#define polyveck_ntt_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_ntt PQCLEAN_DILITHIUM5_CLEAN_polyveck_ntt_jazz

#define polyveck_pack_w1_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_pack_w1 PQCLEAN_DILITHIUM5_CLEAN_polyveck_pack_w1_jazz

#define polyveck_pointwise_poly_montgomery_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_pointwise_poly_montgomery PQCLEAN_DILITHIUM5_CLEAN_polyveck_pointwise_poly_montgomery_jazz

#define polyveck_power2round_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_power2round PQCLEAN_DILITHIUM5_CLEAN_polyveck_power2round_jazz

#define polyveck_reduce_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_reduce PQCLEAN_DILITHIUM5_CLEAN_polyveck_reduce_jazz

#define polyveck_shiftl_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_shiftl PQCLEAN_DILITHIUM5_CLEAN_polyveck_shiftl_jazz

#define polyveck_sub_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_sub PQCLEAN_DILITHIUM5_CLEAN_polyveck_sub_jazz

#define polyveck_uniform_eta_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_uniform_eta PQCLEAN_DILITHIUM5_CLEAN_polyveck_uniform_eta_jazz

#define polyveck_use_hint_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyveck_use_hint PQCLEAN_DILITHIUM5_CLEAN_polyveck_use_hint_jazz

#define polyvecl_add_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_add PQCLEAN_DILITHIUM5_CLEAN_polyvecl_add_jazz

#define polyvecl_chknorm_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_chknorm PQCLEAN_DILITHIUM5_CLEAN_polyvecl_chknorm_jazz

#define polyvecl_invntt_tomont_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_invntt_tomont PQCLEAN_DILITHIUM5_CLEAN_polyvecl_invntt_tomont_jazz

#define polyvecl_ntt_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_ntt PQCLEAN_DILITHIUM5_CLEAN_polyvecl_ntt_jazz

#define polyvecl_pointwise_acc_montgomery_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_acc_montgomery PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_acc_montgomery_jazz

#define polyvecl_pointwise_poly_montgomery_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_poly_montgomery PQCLEAN_DILITHIUM5_CLEAN_polyvecl_pointwise_poly_montgomery_jazz

#define polyvecl_reduce_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_reduce PQCLEAN_DILITHIUM5_CLEAN_polyvecl_reduce_jazz

#define polyvecl_uniform_eta_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_eta PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_eta_jazz

#define polyvecl_uniform_gamma1_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_gamma1 PQCLEAN_DILITHIUM5_CLEAN_polyvecl_uniform_gamma1_jazz

#define polyvec_matrix_expand_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_expand PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_expand_jazz

#define polyvec_matrix_pointwise_montgomery_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_pointwise_montgomery PQCLEAN_DILITHIUM5_CLEAN_polyvec_matrix_pointwise_montgomery_jazz
#endif

// /////////////////////////////////////////////////////////////////////////////
// packing.o
#if 0
#define pack_pk_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_pack_pk PQCLEAN_DILITHIUM5_CLEAN_pack_pk_jazz

#define pack_sig_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_pack_sig PQCLEAN_DILITHIUM5_CLEAN_pack_sig_jazz

#define pack_sk_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_pack_sk PQCLEAN_DILITHIUM5_CLEAN_pack_sk_jazz

#define unpack_pk_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_unpack_pk PQCLEAN_DILITHIUM5_CLEAN_unpack_pk_jazz

#define unpack_sig_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_unpack_sig PQCLEAN_DILITHIUM5_CLEAN_unpack_sig_jazz

#define unpack_sk_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_unpack_sk PQCLEAN_DILITHIUM5_CLEAN_unpack_sk_jazz
#endif

// /////////////////////////////////////////////////////////////////////////////
// sign.o
#if 0
#define crypto_sign_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_crypto_sign PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_jazz

#define crypto_sign_keypair_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_jazz

#define crypto_sign_open_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_open PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_open_jazz

#define crypto_sign_signature_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_signature_jazz

#define crypto_sign_verify_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_verify_jazz
#endif

#endif

#endif
