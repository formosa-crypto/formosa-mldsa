# TODO, to be refactored, write a generic Makefile

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7
#-mcpu=cortex-m4 # not working

test_rouding.out: test_rounding
	./$<

test_rounding:
	$(MAKE) -C ../../ small-testing
	$(ARMCC) -o $@ $(ARMCFLAGS) -static test_rounding.c -I../common -L../../ -ldilithium5_clean

clean:
	rm -f test_rounding
