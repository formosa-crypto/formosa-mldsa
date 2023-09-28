#-------------------------------------------------------------------------------

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7 -fPIC
#-mcpu=cortex-m4 # not working
ARMAR ?= arm-linux-gnueabi-ar

#-------------------------------------------------------------------------------
# This Makefile can be used with GNU Make or BSD Make

LIB=libdilithium5_clean.a
HEADERS=api.h ntt.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h 
OBJECTS=ntt.o packing.o poly.o polyvec.o reduce.o rounding.o sign.o symmetric-shake.o fips202.o library.o

#-------------------------------------------------------------------------------
JASMIN ?= jasminc
JASMIN_FILES := $(subst ./,,$(shell find . -name '*.jazz'))
ASM_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.s)
OBJ_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%_jazz.o)

JASMIN_LIB := library

#-------------------------------------------------------------------------------

default: compile

benjamin:
	$(MAKE) ARMCC=arm-none-eabi-gcc ARMAR=arm-none-eabi-ar default

#-------------------------------------------------------------------------------

$(JASMIN_LIB).o: $(JASMIN_LIB).s
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

$(ASM_JASMIN_FILES):
%.s: %.jazz
	$(JASMIN) -arch=arm-m4 -o $@ $<

.PHONY: $(JASMIN_LIB).jazz
$(JASMIN_LIB).jazz:
	echo "" > $@
	for file in $(filter-out $@, $(JASMIN_FILES)); do \
		echo "require \"$$file\"" >> $@; \
	done

#-------------------------------------------------------------------------------

compile: $(LIB)

%.o: %.c $(HEADERS)
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(ARMAR) -r $@ $(OBJECTS)


#-------------------------------------------------------------------------------
clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
	$(RM) $(ASM_JASMIN_FILES)
	$(RM) $(JASMIN_LIB).*


