#-------------------------------------------------------------------------------

include ../common.mk

#-------------------------------------------------------------------------------

all : clean compile

#-------------------------------------------------------------------------------

JASMIN_LIB := libdilithium_jasmin_test_$(arch).a
JASMIN_OBJECTS := library_test_$(arch).o
JASMIN_FILES := library_test_$(arch).jazz

PRE_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.jpp)
ASM_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.s)
OBJ_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%_jazz.o)

#-------------------------------------------------------------------------------

$(JASMIN_OBJECTS): library_test_$(arch).s
	$(CC) $(CFLAGS) -c -o $@ $<

$(ASM_JASMIN_FILES):
%.s: %.jazz
	$(JASMINC) -arch=$(arch) -o $@ $<

$(JASMIN_LIB): $(JASMIN_OBJECTS)
	$(AR) -r $@ $(JASMIN_OBJECTS)

#-------------------------------------------------------------------------------

PQCLEAN_LIB=libdilithium5_clean.a
PQCLEAN_HEADERS=pqclean/api.h pqclean/ntt.h pqclean/packing.h pqclean/params.h pqclean/poly.h pqclean/polyvec.h pqclean/reduce.h pqclean/rounding.h pqclean/sign.h pqclean/symmetric.h
PQCLEAN_OBJECTS=pqclean/ntt.o pqclean/packing.o pqclean/poly.o pqclean/polyvec.o pqclean/reduce.o pqclean/rounding.o pqclean/sign.o pqclean/symmetric-shake.o pqclean/fips202.o

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(FULL_TESTING) -c -o $@ $<

$(PQCLEAN_LIB): $(PQCLEAN_OBJECTS)
	$(AR) -r $@ $(PQCLEAN_OBJECTS)

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
	$(CC) -o $@ $(CFLAGS) -static test_$*.c -I./common -I./pqclean/ -L./ -ldilithium5_clean -L../ -ldilithium_jasmin_test_$(arch)

#--
.PHONY: clean
clean:
	rm -f $(TESTS_BIN) $(TESTS_OUT) $(PQCLEAN_LIB) $(PQCLEAN_OBJECTS) $(JASMIN_LIB) $(JASMIN_OBJECTS) $(ASM_JASMIN_FILES) $(PRE_JASMIN_FILES) $(OBJ_JASMIN_FILES) library_$(arch).{o,s}
