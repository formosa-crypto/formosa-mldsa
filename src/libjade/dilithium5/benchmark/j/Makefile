#--

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7
ARMAR ?= arm-linux-gnueabi-ar

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	ARMCC := arm-none-eabi-gcc
	ARMCFLAGS := -Wall -O1 -fPIC -mcpu=cortex-m4 -mlittle-endian -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
	ARMAR := arm-none-eabi-ar
endif

JASMIN ?= jasminc

.PHONY: all clean_lib clean_bench compile_lib compile_bench

all: clean compile
compile: compile_lib compile_bench
clean: clean_lib clean_bench

# Rule to generate .s files from .jazz files
library.s: library.jazz
	$(JASMIN) -arch=arm-m4 -o $@ $<

sign_wrap_jazz.o: sign_wrap.c
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

library_jazz.o: library.s
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

# Rule to create the static library
libdilithium5.a: library_jazz.o sign_wrap_jazz.o
	$(ARMAR) -r libdilithium5.a library_jazz.o sign_wrap_jazz.o

compile_lib: libdilithium5.a

clean_lib:
	rm -f library.s library_jazz.o sign_wrap_jazz.o libdilithium5.a


INCLUDES := -I../../test/common -I../../

# Target executable

main.o: main.c
	$(ARMCC) $(ARMCFLAGS) $(INCLUDES) -c -o main.o main.c

# Rules
bench_sign: main.o libdilithium5.a
	$(ARMCC) $(ARMCFLAGS) -o bench_sign main.o -static -L. -ldilithium5

compile_bench: bench_sign

clean_bench:
	rm -f main.o bench_sign
