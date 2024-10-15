# Library compilation

To compile the jasmin Dilithium5 library (libdilithium5_jasmin_risc-v / libdilithium5_jasmin_arm-m4), from the dilithium5 folder:

``` shell
make arch=risc-v
```
 or
 
``` shell
make arch=arm-m4
```

This will generate a library providing the sign API (PQCLEAN_DILITHIUM5_CLEAN_challenge ..).


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
For each jasmin implementation file, it will generate a test (test_sign, test_ntt, test_poly...) that will compare the behavior of the jasmin and the C library.
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
/opt/homebrew/bin/spike --isa=RV32IMAFDC temp/riscv-pk/build/install/riscv32-unknown-elf/bin/pk test_sign
```



