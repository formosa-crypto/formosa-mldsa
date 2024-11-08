#include "version.h"

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


void JASMIN_VERSION(poly_reduce)(poly *a);
void JASMIN_VERSION(poly_caddq)(poly *a);
void JASMIN_VERSION(poly_add)(poly *c, poly *a, poly *b);
uint32_t JASMIN_VERSION(poly_chknorm)(poly *a, int32_t B);
void JASMIN_VERSION(poly_challenge)(poly *c, const uint8_t seed[CTILDEBYTES]);
void JASMIN_VERSION(poly_decompose)(poly *a1, poly *a0, const poly *a);
void JASMIN_VERSION(polyeta_pack)(uint8_t *r, poly *a);
void JASMIN_VERSION(polyeta_unpack)(poly *a, uint8_t *r);

void JASMIN_VERSION(poly_ntt)(poly *a);
void JASMIN_VERSION(poly_invntt_tomont)(poly *a);
void JASMIN_VERSION(poly_pointwise_montgomery)(poly *c, poly *a, poly *b);
uint32_t JASMIN_VERSION(poly_make_hint)(poly *h, poly *a0, poly *a1);
void JASMIN_VERSION(poly_power2round)(poly *a1, poly *a0, poly *a);

void JASMIN_VERSION(poly_shiftl)(poly *a);
void JASMIN_VERSION(poly_sub)(poly *c, poly *a, poly *b);

void JASMIN_VERSION(polyt0_pack)(uint8_t *r, const poly *a);
void JASMIN_VERSION(polyt0_unpack)(poly *r, const uint8_t *a);
void JASMIN_VERSION(polyt1_pack)(uint8_t *r, const poly *a);
void JASMIN_VERSION(polyt1_unpack)(poly *r, const uint8_t *a);

void JASMIN_VERSION(poly_use_hint)(poly *b, poly *a, poly *h);

void JASMIN_VERSION(polyw1_pack)(uint8_t *r, const poly *a);

void JASMIN_VERSION(polyz_pack)(uint8_t *r, const poly *a);
void JASMIN_VERSION(polyz_unpack)(poly *r, const uint8_t *a);
void JASMIN_VERSION(poly_uniform)(poly * a, const uint8_t *seed, uint16_t nonce);
void JASMIN_VERSION(poly_uniform_eta)(poly * a, const uint8_t *seed, uint16_t nonce);
void JASMIN_VERSION(poly_uniform_gamma1)(poly * a, const uint8_t *seed, uint16_t nonce);



int main ()
{
  checkpoly(PQCLEAN_VERSION(poly_reduce), JASMIN_VERSION(poly_reduce), "poly_reduce");
  checkpoly(PQCLEAN_VERSION(poly_caddq), JASMIN_VERSION(poly_caddq), "poly_caddq");
  checkpoly3(PQCLEAN_VERSION(poly_add), JASMIN_VERSION(poly_add), "poly_add");
  checkpolyint(PQCLEAN_VERSION(poly_chknorm), JASMIN_VERSION(poly_chknorm), "poly_chknorm");

  checkpolyseed(PQCLEAN_VERSION(poly_challenge), JASMIN_VERSION(poly_challenge), "poly_challenge");
  checkpoly3(PQCLEAN_VERSION(poly_decompose), JASMIN_VERSION(poly_decompose), "poly_decompose");
  checkpolyetapack(PQCLEAN_VERSION(polyeta_pack), JASMIN_VERSION(polyeta_pack), "polyeta_pack");
  checkpolyetaunpack(PQCLEAN_VERSION(polyeta_unpack), JASMIN_VERSION(polyeta_unpack), "polyeta_unpack");

  checkpoly(PQCLEAN_VERSION(poly_ntt), JASMIN_VERSION(poly_ntt), "poly_ntt");
  checkpoly(PQCLEAN_VERSION(poly_invntt_tomont), JASMIN_VERSION(poly_invntt_tomont), "poly_invntt");
  checkpoly3(PQCLEAN_VERSION(poly_pointwise_montgomery), JASMIN_VERSION(poly_pointwise_montgomery), "poly_pointwize_montomery");

  checkpoly3_u32(PQCLEAN_VERSION(poly_make_hint), JASMIN_VERSION(poly_make_hint), "poly_make_hint");
  checkpoly3(PQCLEAN_VERSION(poly_power2round), JASMIN_VERSION(poly_power2round), "poly_power2round");
  checkpoly(PQCLEAN_VERSION(poly_shiftl), JASMIN_VERSION(poly_shiftl), "poly_shiftl");
  checkpoly3(PQCLEAN_VERSION(poly_sub), JASMIN_VERSION(poly_sub), "poly_sub");

  checkpolyt0pack(PQCLEAN_VERSION(polyt0_pack), JASMIN_VERSION(polyt0_pack), "polyt0_pack");
  checkpolyt0unpack(PQCLEAN_VERSION(polyt0_unpack), JASMIN_VERSION(polyt0_unpack), "polyt0_unpack");

  checkpolyt1pack(PQCLEAN_VERSION(polyt1_pack), JASMIN_VERSION(polyt1_pack), "polyt1_pack");
  checkpolyt1unpack(PQCLEAN_VERSION(polyt1_unpack), JASMIN_VERSION(polyt1_unpack), "polyt1_unpack");

  checkpoly3(PQCLEAN_VERSION(poly_use_hint), JASMIN_VERSION(poly_use_hint), "poly_use_hint");

  checkpolyw1pack(PQCLEAN_VERSION(polyw1_pack), JASMIN_VERSION(polyw1_pack), "polyw1_pack");

  checkpolyzpack(PQCLEAN_VERSION(polyz_pack), JASMIN_VERSION(polyz_pack), "polyz_pack");
  checkpolyzunpack(PQCLEAN_VERSION(polyz_unpack), JASMIN_VERSION(polyz_unpack), "polyz_unpack");

  checkpolyuniform(SEEDBYTES, PQCLEAN_VERSION(poly_uniform), JASMIN_VERSION(poly_uniform), "poly_uniform");
  checkpolyuniform(CRHBYTES, PQCLEAN_VERSION(poly_uniform_eta), JASMIN_VERSION(poly_uniform_eta), "poly_uniform_eta");
  checkpolyuniform(CRHBYTES, PQCLEAN_VERSION(poly_uniform_gamma1), JASMIN_VERSION(poly_uniform_gamma1), "poly_uniform_gamma1");
  
  return 0;
}
