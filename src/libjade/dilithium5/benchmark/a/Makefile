#--

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7
ARMAR ?= arm-linux-gnueabi-ar

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	ARMCC := /Applications/ARM/bin/arm-none-eabi-gcc
	ARMCFLAGS := -Wall -O1 -fPIC -mcpu=cortex-m4 -mlittle-endian -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs 
	ARMAR := /Applications/ARM/bin/arm-none-eabi-ar
endif

JASMIN ?= jasminc

.PHONY: all clean_lib clean_bench compile_lib compile_bench

all: clean compile
compile: compile_lib compile_bench
clean: clean_lib clean_bench

S_FILES := basemul_257.S fnt_257.S ifnt_257.S ntt.S pointwise_mont.s vector.s
H_FILES := api.h config.h fips202.h hal.h keccakf1600.h ntt.h packing.h params.h pointwise_mont.h poly.h polyvec.h randombytes. reduce.h rounding.h sign.h smallntt.h smallpoly.h symmetric.h vector.h
I_FILES := macros.i macros_fnt.i
C_FILES := fips202.c keccakf1600.c packing.c poly.c polyvec.c notrandombytes.c rounding.c sign.c smallpoly.c symmetric-shake.c

C_OBJECTS := $(C_FILES:.c=.o)
S_OBJECTS := $(S_FILES:.S=.o) $(S_FILES:.s=.o)

%.o: %.c
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

# Rule to compile Assembly files to object files
%.o: %.S
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

%.o: %.s
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

libdilithium5.a: $(C_OBJECTS) $(S_OBJECTS)
	$(ARMAR) rcs $@ $^

compile_lib: libdilithium5.a

clean_lib:
	rm -f $(C_OBJECTS) libdilithium5.a


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
