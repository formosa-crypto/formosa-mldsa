# TODO, to be refactored, write a generic Makefile

ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7
#-mcpu=cortex-m4 # not working

test_reduce.out: test_reduce
	./$<

test_reduce:
	$(MAKE) -C ../../ default
	$(ARMCC) -o $@ $(ARMCFLAGS) -static test_reduce.c -I../common -L../../ -ldilithium5_clean

clean:
	rm -f test_reduce
