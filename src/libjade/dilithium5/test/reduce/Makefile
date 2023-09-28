# TODO, to be refactored:

test_reduce.out: test_reduce
	./$<

test_reduce:
	$(MAKE) -C ../../ default
	arm-linux-gnueabi-gcc -o $@ -Wall -O3 -march=armv7 -static test_reduce.c -I../common -L../../ -ldilithium5_clean

clean:
	rm -f test_reduce
