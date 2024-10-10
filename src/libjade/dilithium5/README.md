To compile the jasmin library (libdilithium5_jasmin_risc-v / libdilithium5_jasmin_arm-m4), from the dilithium5 folder:

``` shell
make arch=risc-v
```
 or
 
``` shell
make arch=arm-m4
```


For the sake of testing:

    - We compare pqclean implementation to jasmin implementation on randomly generated input. To that end, we need to ship either one library (with both pqclean and jazz symbols), or two libraries (on with pqclean symbols and the other with jasmin symbols). We opted for the later, the jasmin library is built from the dilithium5 directory, the pqclean library is build from the dilithium5/test directory only for testing purposes. Running the command ```make arch=risc-v``` in the test directory forces the generation of the jasmin library (and the pqclean library).



We had to remove the -fPIC option to avoid the usage of R_RISCV_GOT_HI20 relocation, which was failing upon :

``` shell
/opt/homebrew/bin/riscv64-unknown-elf-gcc -o test_rounding -Wall -O1 -fPIC  -march=rv32im -mabi=ilp32 -static test_rounding.c -I./common -I../ -L../ -ldilithium5_clean
..//libdilithium5_clean.a(library.o): in function `L_round_ref$1':
(.text+0x88cc): dangerous relocation: The addend isn't allowed for R_RISCV_GOT_HI20
```

