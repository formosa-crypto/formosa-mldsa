formosa-mldsa
=======

Jasmin implementations of the pure, hedged version of ML-DSA for **x86-64** and **ARMv7M**.

- [Overview](#overview)
- [Quickstart](#quickstart)

## Overview

This repository contains, for all parameter sets, the following implementations of the pure, hedged version of ML-DSA:

### x86-64

1. A reference implementation (found under `x86-64/ref`).
2. An implementation optimized using the AVX2 instruction set (found under `x86-64/avx2`).

### ARMv7M

1. A reference implementation (found under `arm-m4/ref`).
2. An implementation that minimizes use of stack space (found under `arm-m4/lowram`).

## Quickstart

0. Ensure you have the [Jasmin](https://github.com/jasmin-lang/jasmin) compiler installed,
using the latest commit on the `main` branch of the project. Also ensure that `jasminc` is in the PATH, since this is what the Makefile invokes.

1. To generate assembly code for, say, the AVX2 implementation of ML-DSA-65 on the x86-64 platform, run:

```
env ARCHITECTURE=x86-64 PARAMETER_SET=65 IMPLEMENTATION_TYPE=avx2 make
```

The resulting assembly implementation will be found in `ml_dsa_65_avx2_x86-64.s`.

1. Similarly, to generate assembly code for, say, the minimal-stack-usage implementation of ML-DSA-44 on the ARMv7M platform, run:

```
env ARCHITECTURE=arm-m4 PARAMETER_SET=44 IMPLEMENTATION_TYPE=lowram make
```

The resulting assembly implementation will be found in `ml_dsa_44_lowram_arm-m4.s`.

