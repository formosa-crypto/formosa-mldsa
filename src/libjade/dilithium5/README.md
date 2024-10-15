# Prerequisite

## All platforms

### Retrieve appropriate keccakf1600 implementations from libjade

``` shell
cd *path-to*dilithium-arm
git submodule update
cd ext/libjade
git remote add clebreto git@github.com:clebreto/libjade.git
git fetch clebreto
git checkout -b feature/riscv clebreto/feature/riscv
```

### Retrieve appropriate version of jasmin compiler and compile it

``` shell
git clone git@github.com:jasmin-lang/jasmin.git
cd jasmin
git checkout risc-v-constants-if-while
cd compiler
make CIL -j
make -j
```

## macOS

### Install tools for risc-v cross compilation

``` shell
brew install riscv64-elf-binutils
```

### Install tools for risc-v emulation

#### Spike emulator

``` shell
brew install --cask spike
```

#### pk proxy kernel

``` shell
git clone https://github.com/riscv-software-src/riscv-pk.git
cd riscv-pk
export RISCV="./build/install"
mkdir build
cd build
mkdir install
../configure --prefix=$PWD/install --with-arch=rv32i_zicsr_zifencei --host=riscv64-unknown-elf
make
make install
```

## Linux

# Library compilation

To compile the jasmin Dilithium5 library (libdilithium5_jasmin_risc-v / libdilithium5_jasmin_arm-m4), from the dilithium5 folder:

``` shell
export JASMINC=*path-to*jasminc
```

``` shell
make arch=risc-v
```
 or
 
``` shell
make arch=arm-m4
```

This will generate a library providing the sign API (PQCLEAN_DILITHIUM5_CLEAN_challenge ..). 
More control over which compiler / linker are used can be introspected within common.mk and the Makefile.


# Test compilation and execution

## Compilation

To test independently the internal and external API, from the dilithium5/test folder:

``` shell
make arch=risc-v
```
 or
 
``` shell
make arch=arm-m4
```

This will generate a jasmin library providing internal and external API (from sign, ntt, poly...), as well as a (PQCLEAN) C library with the same API.
For each jasmin implementation file, it will generate a test (test_sign, test_ntt, test_poly...) that will compare the behaviors of the jasmin and the C library.
To that end, both the generated jasmin and C libraries are linked to the tests.

Additional information:

For sake of simplicity, we defined a new PQCLEAN_DILITHIUM5_CLEAN_crypto_sign_keypair_seed function to be able to provide the same random information to both the jasmin and C keypair generation, in order to compare their behaviors.

We had to remove the -fPIC option to avoid the usage of R_RISCV_GOT_HI20 relocation, which was failing upon :

``` shell
/opt/homebrew/bin/riscv64-unknown-elf-gcc -o test_rounding -Wall -O1 -fPIC  -march=rv32im -mabi=ilp32 -static test_rounding.c -I./common -I../ -L../ -ldilithium5_clean
..//libdilithium5_clean.a(library.o): in function `L_round_ref$1':
(.text+0x88cc): dangerous relocation: The addend isn't allowed for R_RISCV_GOT_HI20
```

## Execution

To run the tests using the spike emulator (on Macos: brew install of spike, manual compilation of spike for 32bits RISC-V):

``` shell
/opt/homebrew/bin/spike --isa=RV32IMAFDC *path-to*riscv-pk/build/install/riscv32-unknown-elf/bin/pk test_sign
```



