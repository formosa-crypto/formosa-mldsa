PARAMETER_SET = 65
IMPLEMENTATION_TYPE = ref
# --------------------------------------------------------------------
JASMINC ?= jasminc
JASMINCT ?= jasmin-ct

# --------------------------------------------------------------------
IMPLEMENTATION = ml_dsa_$(PARAMETER_SET)/$(IMPLEMENTATION_TYPE)

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
	cd test && python3 nist_drbg_kat_tests.py && \
			   python3 nist_acvp_tests.py && \
			   python3 wycheproof_verify_tests.py && \
			   python3 wycheproof_sign_tests.py

.PHONY: large-kat-test
large-kat-test: $(OUTPUT_FILE_NAME).so
	cd test && python3 large_kat_test.py

$(OUTPUT_FILE_NAME).so: $(OUTPUT_FILE_NAME).s
	$(CC) $^ -fPIC -shared -o $@

.PHONY: check-ct
check-ct: $(IMPLEMENTATION)/ml_dsa.jazz
	$(JASMINCT) $^

.PHONY: check-sct
check-sct: $(IMPLEMENTATION)/ml_dsa.jazz
	$(JASMINCT) --speculative $^

# --------------------------------------------------------------------
bench.o: $(OUTPUT_FILE_NAME).s bench/bench.c bench/notrandombytes.c
	$(CC) -Wall -Werror \
		  -DIMPLEMENTATION_TYPE=$(IMPLEMENTATION_TYPE) \
		  -DKEYGEN=ml_dsa_$(PARAMETER_SET)_keygen \
		  -DSIGN=ml_dsa_$(PARAMETER_SET)_sign \
		  -DVERIFY=ml_dsa_$(PARAMETER_SET)_verify \
		  -DVERIFICATION_KEY_SIZE=1952 \
		  -DSIGNING_KEY_SIZE=4032 \
		  -DSIGNATURE_SIZE=3309 \
		  $^ -o $@

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr *.s \
		   *.so \
		   *.o
