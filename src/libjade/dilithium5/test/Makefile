#-------------------------------------------------------------------------------

include ../common.mk

#-------------------------------------------------------------------------------

all : compile

#-------------------------------------------------------------------------------

JASMIN_LIB := ../libdilithium_jasmin_risc-v.a

#-------------------------------------------------------------------------------

PQCLEAN_LIB=libdilithium5_clean_$(arch).a
PQCLEAN_HEADERS=pqclean/api.h pqclean/ntt.h pqclean/packing.h pqclean/params.h pqclean/poly.h pqclean/polyvec.h pqclean/reduce.h pqclean/rounding.h pqclean/sign.h pqclean/symmetric.h
PQCLEAN_OBJECTS=pqclean/ntt.o pqclean/packing.o pqclean/poly.o pqclean/polyvec.o pqclean/reduce.o pqclean/rounding.o pqclean/sign.o pqclean/symmetric-shake.o pqclean/fips202.o

%.o: %.c $(HEADERS)
	$(ARMCC) $(ARMCFLAGS) $(FULL_TESTING) -c -o $@ $<

$(PQCLEAN_LIB): $(PQCLEAN_OBJECTS)
	$(ARMAR) -r $@ $(PQCLEAN_OBJECTS)

#-------------------------------------------------------------------------------

TESTS_C := $(subst ./,,$(shell find . -name 'test_*.c'))
TESTS_BIN := $(subst .c,, $(TESTS_C))
TESTS_OUT := $(addsuffix .out, $(TESTS_BIN))

#-- 
default:
	$(MAKE) clean
	$(MAKE) compile
	$(MAKE) run

compile: $(JASMIN_LIB) $(PQCLEAN_LIB) $(TESTS_BIN)
run: $(TESTS_OUT)

%.out: %
	./$< || true # TODO: remove this for CI to fail || keep track of individual failures (this: when there is some time)

$(TESTS_BIN):
test_%: test_%.c ../%.jinc ../%.jazz
	$(ARMCC) -o $@ $(ARMCFLAGS) -static test_$*.c -I./common -I./pqclean/ -L./ -ldilithium5_clean_risc-v -L../ -ldilithium_jasmin_risc-v

$(JASMIN_LIB):
	$(MAKE) -C ..

#--
.PHONY: clean
clean:
	rm -f $(TESTS_BIN) $(TESTS_OUT) $(PQCLEAN_LIB) $(PQCLEAN_OBJECTS)
