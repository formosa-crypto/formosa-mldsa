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

FILES_DIR := ../../
H_FILES := api.h ntt.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h
H_FILE_PATHS := $(addprefix $(FILES_DIR), $(H_FILES))
C_FILES := ntt.c packing.c poly.c polyvec.c reduce.c rounding.c sign.c symmetric-shake.c fips202.c
C_FILE_PATHS := $(addprefix $(FILES_DIR), $(C_FILES))

OBJECTS_C := $(patsubst %.c, %.o, $(notdir $(C_FILE_PATHS)))

%.o: ../../%.c
	@echo "Compiling $<"
	$(ARMCC) $(ARMCFLAGS) -I$(FILES_DIR) -c -o $@ $<

libdilithium5.a : $(OBJECTS_C)
	@echo "Creating library $@"
	$(ARMAR) rcs $@ $^

clean_lib:
	rm -f main.o libdilithium5.a $(OBJECTS_C)

INCLUDES := -I../../test/common -I../../

# Target executable

main.o: main.c
	$(ARMCC) $(ARMCFLAGS) $(INCLUDES) -c -o main.o main.c

# Rules
bench_sign: main.o libdilithium5.a
	$(ARMCC) $(ARMCFLAGS) -o bench_sign main.o -static -L. -ldilithium5 -lc -lm -lgcc

compile_bench: bench_sign

clean_bench:
	rm -f main.o bench_sign
