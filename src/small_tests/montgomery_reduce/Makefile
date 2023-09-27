JASMIN ?= jasminc
ARMCC ?= arm-none-linux-gnueabihf-gcc

all: test
	./test

%_jazz.s: %.jazz
	$(JASMIN) -arch=arm-m4 -o $@ $^

test: montgomery_reduce_8380417_jazz.s
	$(ARMCC) -static -o $@ test.c montgomery_reduce.c ../randombytes/notrandombytes.c $^

.PHONY: clean
clean:
	rm -f test montgomery_reduce_8380417_jazz.s
