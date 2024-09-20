To compile:
```
make


Need to remove the -fPIC option to avoid the usage of R_RISCV_GOT_HI20 relocation, which was failing upon :

``` shell
/opt/homebrew/bin/riscv64-unknown-elf-gcc -o test_rounding -Wall -O1 -fPIC  -march=rv32im -mabi=ilp32 -static test_rounding.c -I./common -I../ -L../ -ldilithium5_clean
..//libdilithium5_clean.a(library.o): in function `L_round_ref$1':
(.text+0x88cc): dangerous relocation: The addend isn't allowed for R_RISCV_GOT_HI20
```






