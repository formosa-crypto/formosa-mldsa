#-------------------------------------------------------------------------------

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7
ARMAR ?= arm-linux-gnueabi-ar

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	ARMCC := /Applications/ARM/bin/arm-none-eabi-gcc
	ARMCFLAGS := -Wall -O1 -fPIC -mcpu=cortex-m4 -mlittle-endian -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
	ARMAR := /Applications/ARM/bin/arm-none-eabi-ar
endif

#-mcpu=cortex-m4 # not working - TODO: check why (same for test/)


#-------------------------------------------------------------------------------
LIB=libdilithium5_clean.a
HEADERS=api.h ntt.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h
OBJECTS=ntt.o packing.o poly.o polyvec.o reduce.o rounding.o sign.o symmetric-shake.o fips202.o library.o

#-------------------------------------------------------------------------------
JASMIN ?= jasminc
PREPROCESSOR ?= ../../../ext/jasmin-preprocessor/preprocessor

JASMIN_FILES := $(subst ./,,$(shell find . -name '*.jazz'))

PRE_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.jpp)
ASM_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.s)
OBJ_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%_jazz.o)

JASMIN_LIB := library

FULL_TESTING ?=

#-------------------------------------------------------------------------------
#-- TODO, improve, done quick

small-testing:
	$(MAKE) clean
	$(MAKE) compile

full-testing:
	$(MAKE) clean
	$(MAKE) FULL_TESTING='-DJAZZ' compile

#-------------------------------------------------------------------------------

benjamin: benjamin-small-testing

benjamin-small-testing:
	$(MAKE) clean
	$(MAKE) ARMCC=arm-none-eabi-gcc ARMAR=arm-none-eabi-ar compile


benjamin-full-testing:
	$(MAKE) clean
	$(MAKE) ARMCC=arm-none-eabi-gcc ARMAR=arm-none-eabi-ar FULL_TESTING='-DJAZZ' compile

#-------------------------------------------------------------------------------

$(JASMIN_LIB).o: $(JASMIN_LIB).s
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

$(ASM_JASMIN_FILES):
%.s: %.jazz
	$(JASMIN) -arch=arm-m4 -o $@ $<

#-------------------------------------------------------------------------------

compile: $(LIB)

%.o: %.c $(HEADERS)
	$(ARMCC) $(ARMCFLAGS) $(FULL_TESTING) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(ARMAR) -r $@ $(OBJECTS)


#-------------------------------------------------------------------------------
clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
	$(RM) $(ASM_JASMIN_FILES)
	$(RM) $(PRE_JASMIN_FILES)
	$(RM) $(JASMIN_LIB).{o,s}
