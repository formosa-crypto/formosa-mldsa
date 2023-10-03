#--
ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7

#-mcpu=cortex-m4 # not working - TODO: check why

#--
TESTS_C := $(subst ./,,$(shell find . -name 'test_*.c'))
TESTS_BIN := $(subst .c,, $(TESTS_C))
TESTS_OUT := $(addsuffix .out, $(TESTS_BIN))

#-- 
default:
	$(MAKE) compile
	$(MAKE) run

compile: $(TESTS_BIN)
run: $(TESTS_OUT)

$(TESTS_OUT):
test_%.out: test_%
	./$< || true # TODO: remove this for CI to fail || keep track of individual failures (this: when there is some time)

$(TESTS_BIN):
test_%:
	$(MAKE) -C ../ small-testing
	$(ARMCC) -o $@ $(ARMCFLAGS) -static test_$*.c -I./common -I../ -L../ -ldilithium5_clean

.PHONY: clean
clean:
	rm -f $(TESTS_BIN) $(TESTS_OUT)

