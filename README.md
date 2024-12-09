# formosa-mldsa (amd64)

This branch contains Jasmin implementations of all 3 parameter-sets of the pure, 
hedged version of ML-DSA, from which one can obtain ML-DSA assembly implementations
for use on the x86-64 platform.

- [Quickstart](#quickstart)

## Quickstart

0. Ensure you have the [Jasmin](https://github.com/jasmin-lang/jasmin) compiler installed,
using the latest commit on the `main` branch of the project. (If you're installing
with nix, [this](https://github.com/formosa-crypto/formosa-mldsa/blob/amd64/shell.nix#L2)
is what we use on CI.). Also ensure that `jasminc` is in the PATH, since this
is what the Makefile invokes.

1. To generate assembly code for, say, the reference implementation of ML-DSA-65,
simply run `env PARAMETER_SET=65 IMPLEMENTATION_TYPE=ref make`. The resulting
assembly implementation will be found in `ml_dsa_65_ref.s`.
