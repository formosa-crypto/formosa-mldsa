#ifndef JASMIN_FUNCTIONS_IMPLEMENTED_H
#define JASMIN_FUNCTIONS_IMPLEMENTED_H

#ifdef JAZZ
// if JAZZ compilation is defined then the 'full compilation' mode is active,
// which means that in the libdilithium5_clean.a the C versions of the functions
// will not be present

#define montgomery_reduce_jazz
#define PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz

#endif

#endif
