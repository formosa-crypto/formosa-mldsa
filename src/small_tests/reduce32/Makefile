JASMIN ?= jasminc
ARMCC ?= arm-none-linux-gnueabihf-gcc

all: test
	./test

%_jazz.s: %.jazz
	$(JASMIN) -arch=arm-m4 -o $@ $^

test: reduce32_8380417_jazz.s
	$(ARMCC) -static -o $@ test.c reduce32.c ../randombytes/notrandombytes.c $^

.PHONY: clean
clean:
	rm -f test reduce32_8380417_jazz.s
