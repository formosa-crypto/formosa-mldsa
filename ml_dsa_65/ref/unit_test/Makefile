JASMINC ?= jasminc
JASMINCT ?= jasmin-ct

.PHONY: test_ntt
test_ntt: ntt.so
	python3 test_ntt.py

ntt.so: ntt.s
	$(CC) $^ -fPIC -shared -o $@

ntt.s: ntt.jazz ../arithmetic/ntt.jinc
	$(JASMINC) -o $@ $<

.PHONY: clean
clean:
	rm -fr *.s \
		   *.so \
		   *.o
