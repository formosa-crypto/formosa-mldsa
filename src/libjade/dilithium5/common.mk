# Configure the target architecture and which compiler to use assemble
ifeq ($(arch), risc-v)
	CC ?= riscv64-unknown-linux-gnu-gcc
	CFLAGS ?= -Wall -O1 -march=rv32im -mabi=ilp32

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		CC := /opt/homebrew/bin/riscv64-unknown-elf-gcc
		CFLAGS := -Wall -O1 -march=rv32im -mabi=ilp32
		AR := /opt/homebrew/bin/riscv64-unknown-elf-ar
	endif
else ifeq ($(arch), arm-m4)
	CC := arm-none-eabi-gcc
	CFLAGS := -Wall -O1 -fPIC -mcpu=cortex-m4 -mlittle-endian -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
	AR ?= riscv64-unknown-linux-gnu-ar
	#-mcpu=cortex-m4 # not working - TODO: check why (same for test/)
else
	$(error arch must be set to risc-v or arm-m4)
endif

JASMINC ?= jasminc
