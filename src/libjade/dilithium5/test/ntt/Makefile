# TODO, to be refactored, write a generic Makefile

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7
#-mcpu=cortex-m4 # not working

test_ntt.out: test_ntt
	./$<

test_ntt:
	$(MAKE) -C ../../ small-testing
	$(ARMCC) -o $@ $(ARMCFLAGS) -static test_ntt.c -I../common -L../../ -ldilithium5_clean

clean:
	rm -f test_ntt
