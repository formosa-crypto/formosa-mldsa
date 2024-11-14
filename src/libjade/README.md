# Compiling the jasmin ML-DSA-(44/65/87) libraries

## Compilation prerequisites

### To all platforms

#### Retrieve appropriate keccakf1600 implementations from libjade (for risc-v)

``` shell
cd *path-to*dilithium-arm
git submodule update
cd ext/libjade
git remote add clebreto git@github.com:clebreto/libjade.git
git fetch clebreto
git checkout -b feature/riscv clebreto/feature/riscv
```

#### Retrieve appropriate version of jasmin compiler, compile it, export it

``` shell
git clone git@github.com:jasmin-lang/jasmin.git
cd jasmin
git checkout risc-v
cd compiler
make CIL -j
make -j
export JASMINC=*path-to*jasminc;
```

### macOS

#### Install tools for risc-v cross compilation

``` shell
brew install riscv64-elf-binutils
```

## Compilation

As an example, to build the jasmin library of ML-DSA-87 for arm-m4:

`cd ml-dsa-87;`
`make arch=arm-m4;`

which produces `libml-dsa-87_jasmin_arm-m4.a`.

This library exposes a subset of the crypto_sign API :
    - JASMIN_MLDSA87_crypto_sign_keypair
    - JASMIN_MLDSA87_crypto_sign_keypair_seed
    - JASMIN_MLDSA87_crypto_sign_signature_ctx
    - JASMIN_MLDSA87_crypto_sign_verify_ctx

## Code organization

### Motivation
  We seeked to minimize code redundancy across versions and architectures in order to minimize efforts for proofs.

### Code structure

Generic implementations with regard to ml-dsa version are located in ml-dsa-any directory.
Specific implementations are located in ml-dsa-$(version) directories.

Implementation variants for arm-m4 and risc-v are provided in these repositories.

The ML-DSA jasmin libraries are built by combining version / architecture generic and specific files according to rules specified in the library-export-$(architecture).jazz located in their respective folders.

# Testing the libraries through emulation (RISC-V)

## Testing prerequisites

### Spike emulator installation

``` shell
brew install --cask spike
```

### pk proxy kernel compilation

``` shell
git clone https://github.com/riscv-software-src/riscv-pk.git
cd riscv-pk
mkdir build
cd build
mkdir install
../configure --prefix=$PWD/install --with-arch=rv32i_zicsr_zifencei --host=riscv64-unknown-elf
make
make install
```

## Tests compilation

`cd ml-dsa-87/test;`
`make arch=risc-v;`

which produces tests executables, `test_sign` among others.

## Tests execution (on OS-X)

As an example, one can run tests overs the `sign` API:

`/opt/homebrew/bin/spike --isa=RV32IMAFDC *path-to-pk*/pk test_sign`
