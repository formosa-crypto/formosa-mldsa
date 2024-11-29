PARAMETER_SET = 65
IMPLEMENTATION_TYPE = ref
# --------------------------------------------------------------------
JASMINC ?= jasminc
JASMINCT ?= jasmin-ct

# --------------------------------------------------------------------
IMPLEMENTATION = $(IMPLEMENTATION_TYPE)/ml_dsa_$(PARAMETER_SET)

IMPLEMENTATION_SOURCES = $(IMPLEMENTATION)/ml_dsa.jazz \
						 $(wildcard $(IMPLEMENTATION)/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/encoding/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/sample/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/arithmetic/*.jinc)

OUTPUT_FILE_NAME = ml_dsa_$(PARAMETER_SET)_$(IMPLEMENTATION_TYPE)

$(OUTPUT_FILE_NAME).s: $(IMPLEMENTATION_SOURCES)
	$(JASMINC) -lazy-regalloc -o $@ $<

# --------------------------------------------------------------------
.PHONY: test
test: $(OUTPUT_FILE_NAME).so
	python3 -m pytest tests/

.PHONY: nist-drbg-kat-test
nist-drbg-kat-test: $(OUTPUT_FILE_NAME).so
	python3 -m pytest tests/test_nist_drbg_kats.py

$(OUTPUT_FILE_NAME).so: $(OUTPUT_FILE_NAME).s
	$(CC) $^ -fPIC -shared -o $@

.PHONY: check-ct
check-ct: $(IMPLEMENTATION)/ml_dsa.jazz
	$(JASMINCT) $^

.PHONY: check-sct
check-sct: $(IMPLEMENTATION)/ml_dsa.jazz
	$(JASMINCT) --speculative $^

# --------------------------------------------------------------------
bench.o: $(OUTPUT_FILE_NAME).s bench/bench.c bench/notrandombytes.c $(IMPLEMENTATION)/api.h
	$(CC) -Wall -Werror \
		  -DIMPLEMENTATION_TYPE=$(IMPLEMENTATION_TYPE) \
		  -DKEYGEN=ml_dsa_$(PARAMETER_SET)_keygen \
		  -DSIGN=ml_dsa_$(PARAMETER_SET)_sign \
		  -DVERIFY=ml_dsa_$(PARAMETER_SET)_verify \
		  $^ -I $(IMPLEMENTATION) -o $@

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr *.s \
		   *.so \
		   *.o
