#-------------------------------------------------------------------------------

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O1 -march=armv7 -fPIC
#-mcpu=cortex-m4 # not working - TODO: check why (same for test/)
ARMAR ?= arm-linux-gnueabi-ar
JASMIN ?= jasminc

.PHONY: all clean compile_c compile_j

all: compile_c compile_j
clean: clean_c clean_j

#-------------------------------------------------------------------------------

LIB_C = libdilithium5_c.a
HEADERS_C = api.h ntt.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h
OBJECTS_C = ntt.o packing.o poly.o polyvec.o reduce.o rounding.o sign.o symmetric-shake.o fips202.o

%.o: %.c $(HEADERS_C)
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

$(LIB_C): $(OBJECTS_C)
	$(ARMAR) rcs $@ $^

compile_c: clean_c $(LIB_C)

clean_c:
	rm -f $(OBJECTS_C) $(LIB_C)

#-------------------------------------------------------------------------------

LIB_J=libdilithium5_j.a
JASMIN_LIB := library
JASMIN_FILES := $(subst ./,,$(shell find . -name '*.jazz'))
PRE_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.jpp)
ASM_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.s)
OBJECTS_J := $(JASMIN_FILES:%.jazz=%_jazz.o)

# Rule to generate .s files from .jazz files
%.s: %.jazz
	$(JASMIN) -arch=arm-m4 -o $@ $<

library_jazz.o: library.s
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

compile_j: clean_j $(LIB_J)

# Rule to create the static library
$(LIB_J): library_jazz.o
	$(ARMAR) -r $@ library_jazz.o

clean_j:
	rm -f $(PRE_JASMIN_FILES) $(ASM_JASMIN_FILES) $(OBJECTS_J) $(LIB_J)


