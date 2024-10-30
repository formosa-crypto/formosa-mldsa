#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <params.h>

#define check32to32(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t arg;							\
    for (int t = 0; t < TESTS; ++t) {					\
      randombytes((uint8_t*)(&arg), sizeof(int32_t));			\
      int32_t res_c = FUNCTION_C(arg);					\
      int32_t res_jazz = FUNCTION_JASMIN(arg);				\
      if (res_c != res_jazz) {						\
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz); \
      printf("FAIL: %s\n", function_name);				\
      exit(1);								\
      }									\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

// int32 x int32 -> int32
#define check3232to32(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  {									\
    int32_t arg1, arg2;							\
    for (int t = 0; t < TESTS; ++t) {					\
      randombytes((uint8_t*)(&arg1), sizeof(int32_t));			\
      randombytes((uint8_t*)(&arg2), sizeof(int32_t));			\
      int32_t res_c = FUNCTION_C(arg1, arg2);				\
      int32_t res_jazz = FUNCTION_JASMIN(arg1, arg2);			\
      if (res_c != res_jazz) {						\
	printf("%" PRId32 ", %" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg1, arg2, res_c, res_jazz); \
	printf("FAIL: %s\n", function_name);				\
	exit(1);							\
      }									\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

  
#define check64to32(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int64_t arg;							\
    for (int t = 0; t < TESTS; ++t) {					\
      randombytes((uint8_t*)(&arg), sizeof(int64_t));			\
      int32_t res_c = FUNCTION_C(arg);					\
      int32_t res_jazz = FUNCTION_JASMIN(arg);				\
      if (res_c != res_jazz) {						\
	printf("%" PRId64 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz); \
	printf("FAIL: %s\n", function_name);				\
	exit(1);							\
      }									\
    }									\
    printf("PASS: %s\n", function_name);				\
  } 

#endif

#define fillarr(ty, k, a)				\
  {							\
    ty arg;						\
    for (int i = 0; i < k; i++) {			\
      randombytes((uint8_t*)(&arg), sizeof(ty));	\
      a[i] = arg;					\
    }							\
  }

#define fillarrN(a, a_jazz)			\
  {						\
    fillarr(int32_t, N, a);			\
    memcpy(a_jazz, a, sizeof(int32_t) * N);	\
  }

#define eqarr(size, PRI, a, a_jazz, function_name)		\
  {								\
    for (int i = 0; i < size; i++) {				\
      if (a[i] != a_jazz[i]) {					\
	printf("at %i : ", i);					\
	printf("%" PRI " != %" PRI "\n", a[i], a_jazz[i]);	\
	printf("FAIL: %s\n", function_name);			\
	exit(1);						\
      }								\
    }								\
  }

#define eqarrN(a, a_jazz, function_name) eqarr(N, PRIx32, a, a_jazz, function_name)

#define checkarrN(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  {								\
    int32_t a[N];						\
    int32_t a_jazz[N];						\
    for(int t=0; t<TESTS; t++)					\
      {								\
	fillarrN(a, a_jazz);					\
	FUNCTION_C(a);						\
	FUNCTION_JASMIN(a_jazz);				\
	eqarrN(a, a_jazz, function_name);			\
      }								\
    printf("PASS: %s\n", function_name);			\
  }

#define checkpoly(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {							      \
    int32_t a[N];					      \
    int32_t a_jazz[N];					      \
    for(int t=0; t<TESTS; t++) {			      \
      fillarrN(a, a_jazz);				      \
      FUNCTION_C((poly *) a);				      \
      FUNCTION_JASMIN((poly *) a_jazz);			      \
      eqarrN(a, a_jazz, function_name);			      \
    }							      \
    printf("PASS: %s\n", function_name);		      \
  }

#define checkpoly3(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t a[N];							\
    int32_t b[N];							\
    int32_t c[N];							\
    int32_t a_jazz[N];							\
    int32_t b_jazz[N];							\
    int32_t c_jazz[N];							\
    for(int t=0; t<TESTS; t++) {					\
	fillarrN(a, a_jazz);						\
	fillarrN(b, b_jazz);						\
	fillarrN(c, c_jazz);						\
	FUNCTION_C((poly *) a, (poly *) b, (poly *) c);			\
	FUNCTION_JASMIN((poly *) a_jazz, (poly *) b_jazz, (poly *) c_jazz); \
	eqarrN(c, c_jazz, function_name " c");				\
	eqarrN(b, b_jazz, function_name " b");				\
	eqarrN(a, a_jazz, function_name " a");				\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpolyint(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								 \
  uint32_t r;							 \
  uint32_t r_jazz;						 \
  uint32_t nonce;						 \
  int32_t a[N];							 \
  int32_t a_jazz[N];						 \
  for(int t=0; t<TESTS; t++) {					 \
    fillarrN(a, a_jazz); \
    fillarr(uint8_t, 4, ((uint8_t*)(&nonce)));	\
    r = FUNCTION_C((poly *) a, nonce); \
    r_jazz = FUNCTION_JASMIN((poly *) a_jazz, nonce); \
    if (r != r_jazz) { \
      printf("result: %" PRId32 " != %" PRId32 "\n", r, r_jazz);	\
      printf("FAIL: %s\n", function_name);				\
      exit(1); }							\
  } \
  printf("PASS: %s\n", function_name); \
  }

#define checkpoly3_u32(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  {                                                                     \
    int32_t a[N];                                                       \
    int32_t b[N];                                                       \
    int32_t c[N];                                                       \
    int32_t a_jazz[N];                                                  \
    int32_t b_jazz[N];                                                  \
    int32_t c_jazz[N];							\
    int32_t r, r_jazz;    						\
    for(int t=0; t<TESTS; t++) {                                        \
      fillarrN(a, a_jazz);						\
      fillarrN(b, b_jazz);						\
      fillarrN(c, c_jazz);						\
      r = FUNCTION_C((poly *) a, (poly *) b, (poly *) c);		\
      r_jazz = FUNCTION_JASMIN((poly *) a_jazz, (poly *) b_jazz, (poly *) c_jazz); \
      eqarrN(c, c_jazz, function_name " c");				\
      eqarrN(b, b_jazz, function_name " b");				\
      eqarrN(a, a_jazz, function_name " a");				\
      if (r != r_jazz) {						\
	printf("result: %" PRId32 " != %" PRId32 "\n", r, r_jazz);	\
	printf("FAIL: %s\n", function_name);				\
	exit(1);							\
      }									\
    }                                                                   \
    printf("PASS: %s\n", function_name);                                \
  }

#define checkpolyseed(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  {									\
    int32_t a[N];							\
    uint8_t seed[CTILDEBYTES];						\
    int32_t a_jazz[N];							\
    for(int t=0; t<TESTS; t++) {					\
      fillarrN(a, a_jazz);						\
      fillarr(uint8_t, CTILDEBYTES, seed);				\
      FUNCTION_C((poly *) a, seed);					\
      FUNCTION_JASMIN((poly *) a_jazz, seed);				\
      eqarrN(a, a_jazz, function_name);					\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpolyetapack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								     \
    int32_t a[N];						     \
    uint8_t r[POLYETA_PACKEDBYTES];				     \
    int32_t a_jazz[N];						     \
    uint8_t r_jazz[POLYETA_PACKEDBYTES];			     \
    for(int t=0; t<TESTS; t++) {				     \
      fillarrN(a, a_jazz);					     \
      fillarr(uint8_t, POLYETA_PACKEDBYTES, r);			     \
      memcpy(r_jazz, r, POLYETA_PACKEDBYTES);			     \
      FUNCTION_C(r, (poly *) a);				     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);			     \
      eqarrN(a, a_jazz, function_name);			     \
      eqarr(POLYETA_PACKEDBYTES, PRIx8, r, r_jazz, function_name);   \
    }								     \
    printf("PASS: %s\n", function_name);			     \
  }

#define checkpolyetaunpack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYETA_PACKEDBYTES];                                  \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYETA_PACKEDBYTES];                             \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYETA_PACKEDBYTES, r);                      \
      memcpy(r_jazz, r, POLYETA_PACKEDBYTES);                        \
      FUNCTION_C((poly *) a, r);				     \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);			     \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYETA_PACKEDBYTES, PRIx8, r, r_jazz, function_name);   \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyt0pack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYT0_PACKEDBYTES];				     \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYT0_PACKEDBYTES];				     \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYT0_PACKEDBYTES, r);			     \
      memcpy(r_jazz, r, POLYT0_PACKEDBYTES);			     \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYT0_PACKEDBYTES, PRIx8, r, r_jazz, function_name);    \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyt0unpack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								      \
    int32_t a[N];						      \
    uint8_t r[POLYT0_PACKEDBYTES];				      \
    int32_t a_jazz[N];						      \
    uint8_t r_jazz[POLYT0_PACKEDBYTES];				      \
    for(int t=0; t<TESTS; t++) {				      \
      fillarrN(a, a_jazz);					      \
      fillarr(uint8_t, POLYT0_PACKEDBYTES, r);			      \
      memcpy(r_jazz, r, POLYT0_PACKEDBYTES);			      \
      FUNCTION_C((poly *) a, r);				      \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);			      \
      eqarrN(a, a_jazz, function_name);				      \
      eqarr(POLYT0_PACKEDBYTES, PRIx8, r, r_jazz, function_name);     \
    }								      \
    printf("PASS: %s\n", function_name);			      \
  }

#define checkpolyt1pack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYT1_PACKEDBYTES];                                   \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYT1_PACKEDBYTES];                              \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYT1_PACKEDBYTES, r);                       \
      memcpy(r_jazz, r, POLYT1_PACKEDBYTES);                         \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYT1_PACKEDBYTES, PRIx8, r, r_jazz, function_name);    \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyt1unpack(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {                                                                   \
    int32_t a[N];                                                     \
    uint8_t r[POLYT1_PACKEDBYTES];                                    \
    int32_t a_jazz[N];                                                \
    uint8_t r_jazz[POLYT1_PACKEDBYTES];                               \
    for(int t=0; t<TESTS; t++) {                                      \
      fillarrN(a, a_jazz);                                            \
      fillarr(uint8_t, POLYT1_PACKEDBYTES, r);                        \
      memcpy(r_jazz, r, POLYT1_PACKEDBYTES);                          \
      FUNCTION_C((poly *) a, r);                                      \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);                       \
      eqarrN(a, a_jazz, function_name);				      \
      eqarr(POLYT1_PACKEDBYTES, PRIx8, r, r_jazz, function_name);     \
    }                                                                 \
    printf("PASS: %s\n", function_name);                              \
  }

#define checkpolyzpack(FUNCTION_C, FUNCTION_JASMIN, function_name)   \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYZ_PACKEDBYTES];				     \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYZ_PACKEDBYTES];				     \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYZ_PACKEDBYTES, r);			     \
      memcpy(r_jazz, r, POLYZ_PACKEDBYTES);			     \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYZ_PACKEDBYTES, PRIx8, r, r_jazz, function_name);     \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyzunpack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                   \
    int32_t a[N];                                                     \
    uint8_t r[POLYZ_PACKEDBYTES];				      \
    int32_t a_jazz[N];                                                \
    uint8_t r_jazz[POLYZ_PACKEDBYTES];				      \
    for(int t=0; t<TESTS; t++) {                                      \
      fillarrN(a, a_jazz);                                            \
      fillarr(uint8_t, POLYZ_PACKEDBYTES, r);			      \
      memcpy(r_jazz, r, POLYZ_PACKEDBYTES);			      \
      FUNCTION_C((poly *) a, r);                                      \
      FUNCTION_JASMIN((poly *) a_jazz, r_jazz);                       \
      eqarrN(a, a_jazz, function_name);				      \
      eqarr(POLYZ_PACKEDBYTES, PRIx8, r, r_jazz, function_name);      \
    }                                                                 \
    printf("PASS: %s\n", function_name);                              \
  }

#define checkpolyw1pack(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                  \
    int32_t a[N];                                                    \
    uint8_t r[POLYW1_PACKEDBYTES];                                   \
    int32_t a_jazz[N];                                               \
    uint8_t r_jazz[POLYW1_PACKEDBYTES];                              \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrN(a, a_jazz);                                           \
      fillarr(uint8_t, POLYW1_PACKEDBYTES, r);                       \
      memcpy(r_jazz, r, POLYW1_PACKEDBYTES);                         \
      FUNCTION_C(r, (poly *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (poly *) a_jazz);                      \
      eqarrN(a, a_jazz, function_name);				     \
      eqarr(POLYW1_PACKEDBYTES, PRIx8, r, r_jazz, function_name);    \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define checkpolyuniform(SIZE, FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {									\
    int32_t a[N];							\
    int32_t a_jazz[N];							\
    uint8_t seed[SIZE];							\
    uint8_t tnonce[2];							\
    for(int t=0; t<TESTS; t++) {					\
      fillarrN(a, a_jazz);						\
      fillarr(uint8_t, SIZE, seed);					\
      fillarr(uint8_t, 2, tnonce);					\
      uint16_t nonce = tnonce[0] | (tnonce[1]<<8);			\
      FUNCTION_C((poly *) a, seed, nonce);				\
      FUNCTION_JASMIN((poly *)a_jazz, seed, nonce);			\
      eqarrN(a, a_jazz, function_name);					\
    }									\
    printf("PASS: %s\n", function_name);				\
  }


#define fillarrNL(a, a_jazz)			\
  {						\
    fillarr(int32_t, N*L, a);			\
    memcpy(a_jazz, a, sizeof(int32_t) * N*L);	\
  }
#define eqarrNL(a, a_jazz, function_name) eqarr(N*L, PRIx32, a, a_jazz, function_name)

#define checkpolyvecluniform(SIZE, FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {									\
    int32_t a[N*L];							\
    int32_t a_jazz[N*L];						\
    uint8_t seed[SIZE];                                                 \
    uint8_t tnonce[2];                                                  \
    for(int t=0; t<TESTS; t++) {                                        \
      fillarrNL(a, a_jazz);					\
      fillarr(uint8_t, SIZE, seed);                                     \
      fillarr(uint8_t, 2, tnonce);                                      \
      uint16_t nonce = tnonce[0] | (tnonce[1]<<8);                      \
      FUNCTION_C((polyvecl *) a, seed, nonce);				\
      FUNCTION_JASMIN((polyvecl *)a_jazz, seed, nonce);			\
      eqarrNL(a, a_jazz, function_name);			\
    }                                                                   \
    printf("PASS: %s\n", function_name);                                \
  }

#define checkpolyvecl(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {                                                               \
    int32_t a[N*L];                                               \
    int32_t a_jazz[N*L];                                          \
    for(int t=0; t<TESTS; t++) {                                  \
      fillarrNL(a, a_jazz);                                  \
      FUNCTION_C((polyvecl *) a);                                 \
      FUNCTION_JASMIN((polyvecl *) a_jazz);                       \
      eqarrNL(a, a_jazz, function_name);             \
    }                                                             \
    printf("PASS: %s\n", function_name);                          \
  }

#define checkpolyvecl3(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t a[N*L];							\
    int32_t b[N*L];							\
    int32_t c[N*L];							\
    int32_t a_jazz[N*L];							\
    int32_t b_jazz[N*L];							\
    int32_t c_jazz[N*L];							\
    for(int t=0; t<TESTS; t++) {					\
  fillarrNL(a, a_jazz);						\
	fillarrNL(b, b_jazz);						\
	fillarrNL(c, c_jazz);						\
	FUNCTION_C((polyvecl *) a, (polyvecl *) b, (polyvecl *) c);			\
	FUNCTION_JASMIN((polyvecl *) a_jazz, (polyvecl *) b_jazz, (polyvecl *) c_jazz); \
	eqarrNL(c, c_jazz, function_name " c");				\
	eqarrNL(b, b_jazz, function_name " b");				\
	eqarrNL(a, a_jazz, function_name " a");				\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpolyvecl_poly(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t a[N*L];							\
    int32_t b[N];							\
    int32_t c[N*L];							\
    int32_t a_jazz[N*L];							\
    int32_t b_jazz[N];							\
    int32_t c_jazz[N*L];							\
    for(int t=0; t<TESTS; t++) {					\
  fillarrNL(a, a_jazz);						\
	fillarrN(b, b_jazz);						\
	fillarrNL(c, c_jazz);						\
	FUNCTION_C((polyvecl *) a, (poly *) b, (polyvecl *) c);			\
	FUNCTION_JASMIN((polyvecl *) a_jazz, (poly *) b_jazz, (polyvecl *) c_jazz); \
	eqarrNL(c, c_jazz, function_name " c");				\
	eqarrN(b, b_jazz, function_name " b");				\
	eqarrNL(a, a_jazz, function_name " a");				\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpoly_polyvecl(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t a[N];							\
    int32_t b[N*L];							\
    int32_t c[N*L];							\
    int32_t a_jazz[N];							\
    int32_t b_jazz[N*L];							\
    int32_t c_jazz[N*L];							\
    for(int t=0; t<TESTS; t++) {					\
  fillarrN(a, a_jazz);						\
	fillarrNL(b, b_jazz);						\
	fillarrNL(c, c_jazz);						\
	FUNCTION_C((poly *) a, (polyvecl *) b, (polyvecl *) c);			\
	FUNCTION_JASMIN((poly *) a_jazz, (polyvecl *) b_jazz, (polyvecl *) c_jazz); \
	eqarrNL(c, c_jazz, function_name " c");				\
	eqarrNL(b, b_jazz, function_name " b");				\
	eqarrN(a, a_jazz, function_name " a");				\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpolyveclint(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								 \
  uint32_t r;							 \
  uint32_t r_jazz;						 \
  uint32_t nonce;						 \
  int32_t a[N*L];							 \
  int32_t a_jazz[N*L];						 \
  for(int t=0; t<TESTS; t++) {					 \
    fillarrNL(a, a_jazz); \
    fillarr(uint8_t, 4, ((uint8_t*)(&nonce)));	\
    r = FUNCTION_C((polyvecl *) a, nonce); \
    r_jazz = FUNCTION_JASMIN((polyvecl *) a_jazz, nonce); \
    if (r != r_jazz) { \
      printf("result: %" PRId32 " != %" PRId32 "\n", r, r_jazz);	\
      printf("FAIL: %s\n", function_name);				\
      exit(1); }							\
  } \
  printf("PASS: %s\n", function_name); \
  }

#define fillarrNK(a, a_jazz)			\
  {						\
    fillarr(int32_t, N*K, a);			\
    memcpy(a_jazz, a, sizeof(int32_t) * N*K);	\
  }
#define eqarrNK(a, a_jazz, function_name) eqarr(N*K, PRIx32, a, a_jazz, function_name)

#define checkpolyveckuniform(SIZE, FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {									\
    int32_t a[N*K];							\
    int32_t a_jazz[N*K];						\
    uint8_t seed[SIZE];                                                 \
    uint8_t tnonce[2];                                                  \
    for(int t=0; t<TESTS; t++) {                                        \
      fillarrNK(a, a_jazz);					\
      fillarr(uint8_t, SIZE, seed);                                     \
      fillarr(uint8_t, 2, tnonce);                                      \
      uint16_t nonce = tnonce[0] | (tnonce[1]<<8);                      \
      FUNCTION_C((polyveck *) a, seed, nonce);				\
      FUNCTION_JASMIN((polyveck *)a_jazz, seed, nonce);			\
      eqarrNK(a, a_jazz, function_name);			\
    }                                                                   \
    printf("PASS: %s\n", function_name);                                \
  }

#define checkpolyveck(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {                                                               \
    int32_t a[N*K];                                               \
    int32_t a_jazz[N*K];                                          \
    for(int t=0; t<TESTS; t++) {                                  \
      fillarrNK(a, a_jazz);                                  \
      FUNCTION_C((polyveck *) a);                                 \
      FUNCTION_JASMIN((polyveck *) a_jazz);                       \
      eqarrNK(a, a_jazz, function_name);             \
    }                                                             \
    printf("PASS: %s\n", function_name);                          \
  }

#define checkpolyveck3(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t a[N*K];							\
    int32_t b[N*K];							\
    int32_t c[N*K];							\
    int32_t a_jazz[N*K];							\
    int32_t b_jazz[N*K];							\
    int32_t c_jazz[N*K];							\
    for(int t=0; t<TESTS; t++) {					\
  fillarrNK(a, a_jazz);						\
	fillarrNK(b, b_jazz);						\
	fillarrNK(c, c_jazz);						\
	FUNCTION_C((polyveck *) a, (polyveck *) b, (polyveck *) c);			\
	FUNCTION_JASMIN((polyveck *) a_jazz, (polyveck *) b_jazz, (polyveck *) c_jazz); \
	eqarrNK(c, c_jazz, function_name " c");				\
	eqarrNK(b, b_jazz, function_name " b");				\
	eqarrNK(a, a_jazz, function_name " a");				\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpolyveck_poly(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t a[N*K];							\
    int32_t b[N];							\
    int32_t c[N*K];							\
    int32_t a_jazz[N*K];							\
    int32_t b_jazz[N];							\
    int32_t c_jazz[N*K];							\
    for(int t=0; t<TESTS; t++) {					\
  fillarrNK(a, a_jazz);						\
	fillarrN(b, b_jazz);						\
	fillarrNK(c, c_jazz);						\
	FUNCTION_C((polyveck *) a, (poly *) b, (polyveck *) c);			\
	FUNCTION_JASMIN((polyveck *) a_jazz, (poly *) b_jazz, (polyveck *) c_jazz); \
	eqarrNK(c, c_jazz, function_name " c");				\
	eqarrN(b, b_jazz, function_name " b");				\
	eqarrNK(a, a_jazz, function_name " a");				\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpolyveckint(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								 \
  uint32_t r;							 \
  uint32_t r_jazz;						 \
  uint32_t nonce;						 \
  int32_t a[N*K];							 \
  int32_t a_jazz[N*K];						 \
  for(int t=0; t<TESTS; t++) {					 \
    fillarrNK(a, a_jazz); \
    fillarr(uint8_t, 4, ((uint8_t*)(&nonce)));	\
    r = FUNCTION_C((polyveck *) a, nonce); \
    r_jazz = FUNCTION_JASMIN((polyveck *) a_jazz, nonce); \
    if (r != r_jazz) { \
      printf("result: %" PRId32 " != %" PRId32 "\n", r, r_jazz);	\
      printf("FAIL: %s\n", function_name);				\
      exit(1); }							\
  } \
  printf("PASS: %s\n", function_name); \
  }

#define checkpolyveck3_u32(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  {                                                                     \
    int32_t a[N*K];                                                       \
    int32_t b[N*K];                                                       \
    int32_t c[N*K];                                                       \
    int32_t a_jazz[N*K];                                                  \
    int32_t b_jazz[N*K];                                                  \
    int32_t c_jazz[N*K];							\
    int32_t r, r_jazz;    						\
    for(int t=0; t<TESTS; t++) {                                        \
      fillarrNK(a, a_jazz);						\
      fillarrNK(b, b_jazz);						\
      fillarrNK(c, c_jazz);						\
      r = FUNCTION_C((polyveck *) a, (polyveck *) b, (polyveck *) c);		\
      r_jazz = FUNCTION_JASMIN((polyveck *) a_jazz, (polyveck *) b_jazz, (polyveck *) c_jazz); \
      eqarrNK(c, c_jazz, function_name " c");				\
      eqarrNK(b, b_jazz, function_name " b");				\
      eqarrNK(a, a_jazz, function_name " a");				\
      if (r != r_jazz) {						\
	printf("result: %" PRId32 " != %" PRId32 "\n", r, r_jazz);	\
	printf("FAIL: %s\n", function_name);				\
	exit(1);							\
      }									\
    }                                                                   \
    printf("PASS: %s\n", function_name);                                \
  }

#define checkpolyveckpackw1(FUNCTION_C, FUNCTION_JASMIN, function_name)  \
  {                                                                  \
    int32_t a[N*K];                                                    \
    uint8_t r[POLYW1_PACKEDBYTES*K];                                   \
    int32_t a_jazz[N*K];                                               \
    uint8_t r_jazz[POLYW1_PACKEDBYTES*K];                              \
    for(int t=0; t<TESTS; t++) {                                     \
      fillarrNK(a, a_jazz);                                           \
      fillarr(uint8_t, POLYW1_PACKEDBYTES*K, r);                       \
      memcpy(r_jazz, r, POLYW1_PACKEDBYTES*K);                         \
      FUNCTION_C(r, (polyveck *) a);                                     \
      FUNCTION_JASMIN(r_jazz, (polyveck *) a_jazz);                      \
      eqarrNK(a, a_jazz, function_name);				     \
      eqarr(POLYW1_PACKEDBYTES*K, PRIx8, r, r_jazz, function_name);    \
    }                                                                \
    printf("PASS: %s\n", function_name);                             \
  }

#define fillarrNKL(a, a_jazz)			\
  {						\
    fillarr(int32_t, N*K*L, a);			\
    memcpy(a_jazz, a, sizeof(int32_t) * N*K*L);	\
  }
#define eqarrNKL(a, a_jazz, function_name) eqarr(N*K*L, PRIx32, a, a_jazz, function_name)

#define checkmat(SIZE, FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {									\
    int32_t a[N*K*L];							\
    int32_t a_jazz[N*K*L];							\
    uint8_t seed[SIZE];							\
    for(int t=0; t<TESTS; t++) {					\
      fillarrNKL(a, a_jazz);						\
      fillarr(uint8_t, SIZE, seed);					\
      FUNCTION_C((polyvecl *) a, seed);				\
      FUNCTION_JASMIN((polyvecl *) a_jazz, seed);			\
      eqarrNKL(a, a_jazz, function_name);					\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define checkpolyvecl_mat(FUNCTION_C, FUNCTION_JASMIN, function_name)		\
  {									\
    int32_t a[N*K];							\
    int32_t b[N*K*L];							\
    int32_t c[N*L];							\
    int32_t a_jazz[N*K];							\
    int32_t b_jazz[N*K*L];							\
    int32_t c_jazz[N*L];							\
    for(int t=0; t<TESTS; t++) {					\
  fillarrNK(a, a_jazz);						\
	fillarrNKL(b, b_jazz);						\
	fillarrNL(c, c_jazz);						\
	FUNCTION_C((polyveck *) a, (polyvecl *) b, (polyvecl *) c);			\
	FUNCTION_JASMIN((polyveck *) a_jazz, (polyvecl *) b_jazz, (polyvecl *) c_jazz); \
	eqarrNL(c, c_jazz, function_name " c");				\
	eqarrNKL(b, b_jazz, function_name " b");				\
	eqarrNK(a, a_jazz, function_name " a");				\
    }									\
    printf("PASS: %s\n", function_name);				\
  }

#define fillarrni32(a, a_jazz, n)			\
  {						\
    fillarr(int32_t, n, a);			\
    memcpy(a_jazz, a, sizeof(int32_t) * n);	\
  }
#define fillarrnu8(a, a_jazz, n)			\
  {						\
    fillarr(uint8_t, n, a);			\
    memcpy(a_jazz, a, sizeof(uint8_t) * n);	\
  }

#define check_pk_rhot1(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								 \
  int32_t t1[N*K];							 \
  int32_t t1_jazz[N*K];						 \
  uint8_t rho[SEEDBYTES];						 \
  uint8_t rho_jazz[SEEDBYTES];		\
  uint8_t pk[JASMIN_MLDSA65_CRYPTO_PUBLICKEYBYTES]; \
  uint8_t pk_jazz[JASMIN_MLDSA65_CRYPTO_PUBLICKEYBYTES]; \
  for(int t=0; t<TESTS; t++) {	 \
    fillarrni32(t1, t1_jazz, N*K); \
    fillarrnu8(rho, rho_jazz, SEEDBYTES);	\
    FUNCTION_C(pk, rho, (polyveck *) t1); \
    FUNCTION_JASMIN(pk_jazz, rho_jazz, (polyveck *) t1_jazz); \
    eqarr(JASMIN_MLDSA65_CRYPTO_PUBLICKEYBYTES, PRId8, pk, pk_jazz, function_name) \
  } \
  printf("PASS: %s\n", function_name); \
  } 

#define check_rhot1_pk(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  {								 \
  int32_t t1[N*K];							 \
  int32_t t1_jazz[N*K];						 \
  uint8_t rho[SEEDBYTES];						 \
  uint8_t rho_jazz[SEEDBYTES];		\
  uint8_t pk[JASMIN_MLDSA65_CRYPTO_PUBLICKEYBYTES]; \
  uint8_t pk_jazz[JASMIN_MLDSA65_CRYPTO_PUBLICKEYBYTES]; \
  for(int t=0; t<TESTS; t++) {	 \
    fillarrnu8(pk, pk_jazz, JASMIN_MLDSA65_CRYPTO_PUBLICKEYBYTES); \
    FUNCTION_C(rho, (polyveck *) t1, pk); \
    FUNCTION_JASMIN(rho_jazz, (polyveck *) t1_jazz, pk_jazz); \
    eqarr(N*K, PRId32, t1, t1_jazz, function_name) \
    eqarr(SEEDBYTES, PRId8, rho, rho_jazz, function_name) \
  } \
  printf("PASS: %s\n", function_name); \
  } 

  #define check_sk_rhotrkeyt0s1s2(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
    int32_t t0[N*K];							 \
    int32_t t0_jazz[N*K];						 \
    int32_t s1[N*L];							 \
    int32_t s1_jazz[N*L];						 \
    int32_t s2[N*K];							 \
    int32_t s2_jazz[N*K];						 \
    uint8_t rho[SEEDBYTES];						 \
    uint8_t rho_jazz[SEEDBYTES];		\
    uint8_t tr[TRBYTES];						 \
    uint8_t tr_jazz[TRBYTES];		\
    uint8_t key[SEEDBYTES];						 \
    uint8_t key_jazz[SEEDBYTES];		\
    uint8_t sk[JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES]; \
    uint8_t sk_jazz[JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES]; \
    for(int t=0; t<TESTS; t++) {	 \
        fillarrni32(t0, t0_jazz, N*K); \
        fillarrni32(s1, s1_jazz, N*L); \
        fillarrni32(s2, s2_jazz, N*K); \
        fillarrnu8(rho, rho_jazz, SEEDBYTES);	\
        fillarrnu8(tr, tr_jazz, TRBYTES);	\
        fillarrnu8(key, key_jazz, SEEDBYTES);	\
        FUNCTION_C(sk, rho, tr, key, (polyveck *) t0, (polyvecl *) s1, (polyveck *) s2); \
        FUNCTION_JASMIN(sk_jazz, rho_jazz, tr_jazz, key_jazz, (polyveck *) t0_jazz, (polyvecl *) s1_jazz, (polyveck *) s2_jazz); \
        eqarr(JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES, PRId8, sk, sk_jazz, function_name) \
    } \
    printf("PASS: %s\n", function_name); \
  }

  #define check_rhotrkeyt0s1s2_sk(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
    int32_t t0[N*K];							 \
    int32_t t0_jazz[N*K];						 \
    int32_t s1[N*L];							 \
    int32_t s1_jazz[N*L];						 \
    int32_t s2[N*K];							 \
    int32_t s2_jazz[N*K];						 \
    uint8_t rho[SEEDBYTES];						 \
    uint8_t rho_jazz[SEEDBYTES];		\
    uint8_t tr[TRBYTES];						 \
    uint8_t tr_jazz[TRBYTES];		\
    uint8_t key[SEEDBYTES];						 \
    uint8_t key_jazz[SEEDBYTES];		\
    uint8_t sk[JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES]; \
    uint8_t sk_jazz[JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES]; \
    for(int t=0; t<TESTS; t++) {	 \
        fillarrnu8(sk, sk_jazz, JASMIN_MLDSA65_CRYPTO_SECRETKEYBYTES); \
        FUNCTION_C(rho, tr, key, (polyveck *) t0, (polyvecl *) s1, (polyveck *) s2, sk); \
        FUNCTION_JASMIN(rho_jazz, tr_jazz, key_jazz, (polyveck *) t0_jazz, (polyvecl *) s1_jazz, (polyveck *) s2_jazz, sk_jazz); \
        eqarr(N*K, PRId32, t0, t0_jazz, function_name) \
        eqarr(N*L, PRId32, s1, s1_jazz, function_name) \
        eqarr(N*K, PRId32, s2, s2_jazz, function_name) \
        eqarr(SEEDBYTES, PRId8, rho, rho_jazz, function_name) \
        eqarr(TRBYTES, PRId8, tr, tr_jazz, function_name) \
        eqarr(SEEDBYTES, PRId8, key, key_jazz, function_name) \
    } \
    printf("PASS: %s\n", function_name); \
  }


