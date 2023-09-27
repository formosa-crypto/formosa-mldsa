JASMIN ?= jasminc
ARMCC ?= arm-none-linux-gnueabihf-gcc

all: test
	./test

%_jazz.s: %.jazz
	$(JASMIN) -arch=arm-m4 -o $@ $^

test: caddq_jazz.s
	$(ARMCC) -static -o $@ test.c caddq.c ../randombytes/notrandombytes.c $^

.PHONY: clean
clean:
	rm -f test caddq_jazz.s
