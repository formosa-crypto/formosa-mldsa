#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "poly.h"
#include "notrandombytes.c"
#include "fips202.h"
#include "test_macros.h"

#ifndef TESTS
#define TESTS 1000
#endif


void JASMIN_MLDSA65_poly_reduce(poly *a);
void JASMIN_MLDSA65_poly_caddq(poly *a);
void JASMIN_MLDSA65_poly_add(poly *c, poly *a, poly *b);
void JASMIN_MLDSA65_poly_add_inplace(poly *c, poly *a, poly *b);
uint32_t JASMIN_MLDSA65_poly_chknorm(poly *a, int32_t B);
void JASMIN_MLDSA65_poly_challenge(poly *c, const uint8_t seed[CTILDEBYTES]);
void JASMIN_MLDSA65_poly_decompose(poly *a1, poly *a0, const poly *a);
void JASMIN_MLDSA65_polyeta_pack(uint8_t *r, poly *a);
void JASMIN_MLDSA65_polyeta_unpack(poly *a, uint8_t *r);

void JASMIN_MLDSA65_poly_ntt(poly *a);
void JASMIN_MLDSA65_poly_invntt_tomont(poly *a);
void JASMIN_MLDSA65_poly_pointwise_montgomery(poly *c, poly *a, poly *b);
uint32_t JASMIN_MLDSA65_poly_make_hint(poly *h, poly *a0, poly *a1);
void JASMIN_MLDSA65_poly_power2round(poly *a1, poly *a0, poly *a);

void JASMIN_MLDSA65_poly_shiftl(poly *a);
void JASMIN_MLDSA65_poly_sub(poly *c, poly *a, poly *b);

void JASMIN_MLDSA65_polyt0_pack(uint8_t *r, const poly *a);
void JASMIN_MLDSA65_polyt0_unpack(poly *r, const uint8_t *a);
void JASMIN_MLDSA65_polyt1_pack(uint8_t *r, const poly *a);
void JASMIN_MLDSA65_polyt1_unpack(poly *r, const uint8_t *a);

void JASMIN_MLDSA65_poly_use_hint(poly *b, poly *a, poly *h);

void JASMIN_MLDSA65_polyw1_pack(uint8_t *r, const poly *a);

void JASMIN_MLDSA65_polyz_pack(uint8_t *r, const poly *a);
void JASMIN_MLDSA65_polyz_unpack(poly *r, const uint8_t *a);
void JASMIN_MLDSA65_poly_uniform(poly * a, const uint8_t *seed, uint16_t nonce);
void JASMIN_MLDSA65_poly_uniform_eta(poly * a, const uint8_t *seed, uint16_t nonce);
void JASMIN_MLDSA65_poly_uniform_gamma1(poly * a, const uint8_t *seed, uint16_t nonce);



int main ()
{
  checkpoly(PQCLEAN_MLDSA65_CLEAN_poly_reduce, JASMIN_MLDSA65_poly_reduce, "poly_reduce");
  checkpoly(PQCLEAN_MLDSA65_CLEAN_poly_caddq, JASMIN_MLDSA65_poly_caddq, "poly_caddq");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_add, JASMIN_MLDSA65_poly_add, "poly_add");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_add, JASMIN_MLDSA65_poly_add_inplace, "poly_add_inplace");
  checkpolyint(PQCLEAN_MLDSA65_CLEAN_poly_chknorm, JASMIN_MLDSA65_poly_chknorm, "poly_chknorm");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_add, JASMIN_MLDSA65_poly_add, "poly_add");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_add, JASMIN_MLDSA65_poly_add_inplace, "poly_add_inplace");
  
  checkpolyseed(PQCLEAN_MLDSA65_CLEAN_poly_challenge, JASMIN_MLDSA65_poly_challenge, "poly_challenge");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_decompose, JASMIN_MLDSA65_poly_decompose, "poly_decompose");
  checkpolyetapack(PQCLEAN_MLDSA65_CLEAN_polyeta_pack, JASMIN_MLDSA65_polyeta_pack, "polyeta_pack");
  checkpolyetaunpack(PQCLEAN_MLDSA65_CLEAN_polyeta_unpack, JASMIN_MLDSA65_polyeta_unpack, "polyeta_unpack");

  checkpoly(PQCLEAN_MLDSA65_CLEAN_poly_ntt, JASMIN_MLDSA65_poly_ntt, "poly_ntt");
  checkpoly(PQCLEAN_MLDSA65_CLEAN_poly_invntt_tomont, JASMIN_MLDSA65_poly_invntt_tomont, "poly_invntt");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_pointwise_montgomery, JASMIN_MLDSA65_poly_pointwise_montgomery, "poly_pointwize_montomery");

  checkpoly3_u32(PQCLEAN_MLDSA65_CLEAN_poly_make_hint, JASMIN_MLDSA65_poly_make_hint, "poly_make_hint");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_power2round, JASMIN_MLDSA65_poly_power2round, "poly_power2round");
  checkpoly(PQCLEAN_MLDSA65_CLEAN_poly_shiftl, JASMIN_MLDSA65_poly_shiftl, "poly_shiftl");
  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_sub, JASMIN_MLDSA65_poly_sub, "poly_sub");

  checkpolyt0pack(PQCLEAN_MLDSA65_CLEAN_polyt0_pack, JASMIN_MLDSA65_polyt0_pack, "polyt0_pack");
  checkpolyt0unpack(PQCLEAN_MLDSA65_CLEAN_polyt0_unpack, JASMIN_MLDSA65_polyt0_unpack, "polyt0_unpack");

  checkpolyt1pack(PQCLEAN_MLDSA65_CLEAN_polyt1_pack, JASMIN_MLDSA65_polyt1_pack, "polyt1_pack");
  checkpolyt1unpack(PQCLEAN_MLDSA65_CLEAN_polyt1_unpack, JASMIN_MLDSA65_polyt1_unpack, "polyt1_unpack");

  checkpoly3(PQCLEAN_MLDSA65_CLEAN_poly_use_hint, JASMIN_MLDSA65_poly_use_hint, "poly_use_hint");

  checkpolyw1pack(PQCLEAN_MLDSA65_CLEAN_polyw1_pack, JASMIN_MLDSA65_polyw1_pack, "polyw1_pack");

  checkpolyzpack(PQCLEAN_MLDSA65_CLEAN_polyz_pack, JASMIN_MLDSA65_polyz_pack, "polyz_pack");
  checkpolyzunpack(PQCLEAN_MLDSA65_CLEAN_polyz_unpack, JASMIN_MLDSA65_polyz_unpack, "polyz_unpack");

  checkpolyuniform(SEEDBYTES, PQCLEAN_MLDSA65_CLEAN_poly_uniform, JASMIN_MLDSA65_poly_uniform, "poly_uniform");
  checkpolyuniform(CRHBYTES, PQCLEAN_MLDSA65_CLEAN_poly_uniform_eta, JASMIN_MLDSA65_poly_uniform_eta, "poly_uniform_eta");
  checkpolyuniform(CRHBYTES, PQCLEAN_MLDSA65_CLEAN_poly_uniform_gamma1, JASMIN_MLDSA65_poly_uniform_gamma1, "poly_uniform_gamma1");
  
  return 0;
}
