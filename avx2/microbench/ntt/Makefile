JASMINC ?= jasminc

ntt.s: ntt.jazz
	$(JASMINC) -o $@ $<

bench.o: bench.c ntt.s
	$(CC) -Wall -Werror $^ -o $@

.PHONY: clean
clean:
	rm -fr *.s *.o
