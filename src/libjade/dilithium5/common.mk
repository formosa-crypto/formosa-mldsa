# Configure the target architecture and which compiler to use assemble
ifeq ($(arch), risc-v)
	ARMCC ?= riscv64-unknown-linux-gnu-gcc
	ARMCFLAGS ?= -Wall -O1 -march=rv32im -mabi=ilp32
	ARMAR ?= riscv64-unknown-linux-gnu-ar

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		ARMCC := /opt/homebrew/bin/riscv64-unknown-elf-gcc
		ARMCFLAGS := -Wall -O1 -march=rv32im -mabi=ilp32
		ARMAR := /opt/homebrew/bin/riscv64-unknown-elf-ar
	endif
else ifeq ($(arch), arm-m4)
	ARMCC := arm-none-eabi-gcc
	ARMCFLAGS := -Wall -O1 -fPIC -mcpu=cortex-m4 -mlittle-endian -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
	#-mcpu=cortex-m4 # not working - TODO: check why (same for test/)
else
	$(error arch must be set to risc-v or arm-m4)
endif

JASMINC ?= jasminc
