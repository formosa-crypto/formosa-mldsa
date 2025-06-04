Jasmin implementations of ML-DSA
=======

This branch contains Jasmin implementations of all 3 parameter-sets of the pure, 
hedged version of ML-DSA, from which one can obtain ML-DSA assembly implementations
for use on the x86-64 and ARMv7M platforms.

- [Quickstart](#quickstart)

## Quickstart

0. Ensure you have the [Jasmin](https://github.com/jasmin-lang/jasmin) compiler installed,
using the latest commit on the `main` branch of the project. Also ensure that `jasminc` is in the PATH, since this is what the Makefile invokes.

1. To generate assembly code for, say, the AVX2 implementation of ML-DSA-65 on the x86-64 platform, simply run `env ARCHITECTURE=x86-64 PARAMETER_SET=65 IMPLEMENTATION_TYPE=avx2 make`. The resulting assembly implementation will be found in `ml_dsa_65_avx2_x86-64.s`.
