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
