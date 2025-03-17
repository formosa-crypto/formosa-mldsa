JASMINC ?= jasminc

wrapper.s: wrapper.jazz
	$(JASMINC) -o $@ $<

bench.o: bench.c wrapper.s
	$(CC) -Wall -Werror $^ -o $@

.PHONY: clean
clean:
	rm -fr *.s *.o
