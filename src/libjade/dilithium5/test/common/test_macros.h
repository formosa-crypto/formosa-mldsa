#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define check32to32(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  { \
  int32_t arg; \
  for (int t = 0; t < TESTS; ++t) { \
    randombytes((uint8_t*)(&arg), sizeof(int32_t)); \
    int32_t res_c = FUNCTION_C(arg); \
    int32_t res_jazz = FUNCTION_JASMIN(arg); \
    if (res_c != res_jazz) { \
      printf("%" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz); \
      printf("FAIL: %s\n", function_name); \
      exit(1); \
    } \
  } \
  printf("PASS: %s\n", function_name); \
  }

// int32 x int32 -> int32
#define check3232to32(FUNCTION_C, FUNCTION_JASMIN, function_name)	\
  { \
  int32_t arg1, arg2; \
  for (int t = 0; t < TESTS; ++t) { \
    randombytes((uint8_t*)(&arg1), sizeof(int32_t)); \
    randombytes((uint8_t*)(&arg2), sizeof(int32_t)); \
    int32_t res_c = FUNCTION_C(arg1, arg2); \
    int32_t res_jazz = FUNCTION_JASMIN(arg1, arg2); \
    if (res_c != res_jazz) { \
      printf("%" PRId32 ", %" PRId32 " -> %" PRId32 " != %" PRId32 "\n", arg1, arg2, res_c, res_jazz); \
      printf("FAIL: %s\n", function_name); \
      exit(1); \
    } \
  } \
  printf("PASS: %s\n", function_name); \
  }

  
#define check64to32(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
  int64_t arg; \
  for (int t = 0; t < TESTS; ++t) { \
    randombytes((uint8_t*)(&arg), sizeof(int64_t)); \
    int32_t res_c = FUNCTION_C(arg); \
    int32_t res_jazz = FUNCTION_JASMIN(arg); \
    if (res_c != res_jazz) { \
      printf("%" PRId64 " -> %" PRId32 " != %" PRId32 "\n", arg, res_c, res_jazz); \
      printf("FAIL: %s\n", function_name); \
      exit(1); \
    } \
  } \
  printf("PASS: %s\n", function_name); \
  } 

#endif

#define fillarr(ty, k, a)			\
  { \
  ty arg; \
  for (int i = 0; i < k; i++) { \
    randombytes((uint8_t*)(&arg), sizeof(ty)); \
    a[i] = arg; \
  } \
  }

#define fillarrN(a, a_jazz) \
  { \
  fillarr(int32_t, N, a); \
  memcpy(a_jazz, a, sizeof(int32_t) * N); \
  }

#define eqarrN(a, a_jazz, function_name)			\
  { \
  for (int i = 0; i < N; i++) { \
    if (a[i] != a_jazz[i]) { \
      printf("at %i : ", i); \
      printf(PRId32 " != %" PRId32 "\n", a[i], a_jazz[i]);	\
      printf("FAIL: %s\n", function_name); \
      exit(1); \
    } \
  } \
  }

#define checkarrN(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
  int32_t a[N]; \
  int32_t a_jazz[N]; \
  for(int t=0; t<TESTS; t++) \
  { \
    fillarrN(a, a_jazz); \
    FUNCTION_C(a);	     \
    FUNCTION_JASMIN(a_jazz); \
    eqarrN(a, a_jazz, function_name); \
  } \
  printf("PASS: %s\n", function_name); \
  }

#define checkpoly(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
  int32_t a[N]; \
  int32_t a_jazz[N]; \
  for(int t=0; t<TESTS; t++) \
  { \
    fillarrN(a, a_jazz); \
    FUNCTION_C((poly *) a); \
    FUNCTION_JASMIN((poly *) a_jazz); \
    eqarrN(a, a_jazz, function_name); \
  } \
  printf("PASS: %s\n", function_name); \
  }

#define checkpoly2(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
  int32_t a[N]; \
  int32_t b[N]; \
  int32_t c[N];	\
  int32_t a_jazz[N]; \
  int32_t b_jazz[N]; \
  int32_t c_jazz[N]; \
  for(int t=0; t<TESTS; t++) \
  { \
    fillarrN(a, a_jazz); \
    fillarrN(b, b_jazz); \
    FUNCTION_C((poly *) c, (poly *) a, (poly *) b); \
    FUNCTION_JASMIN((poly *) c_jazz, (poly *) a_jazz, (poly *) b_jazz); \
    eqarrN(c, c_jazz, function_name); \
  } \
  printf("PASS: %s\n", function_name); \
  }

#define checkpolyint(FUNCTION_C, FUNCTION_JASMIN, function_name) \
  { \
  int r; \
  int r_jazz; \
  int32_t a[N]; \
  int32_t a_jazz[N]; \
  for(int t=0; t<TESTS; t++) \
  { \
    fillarrN(a, a_jazz); \
    FUNCTION_C((poly *) a, 3); \
    FUNCTION_JASMIN((poly *) a_jazz, 3); \
    eqarrN(a, a_jazz, function_name); \
  } \
  printf("PASS: %s\n", function_name); \
  }
