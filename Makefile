PARAMETER_SET ?= 65
IMPLEMENTATION_TYPE ?= ref

COMMON = $(IMPLEMENTATION_TYPE)/common
IMPLEMENTATION = $(IMPLEMENTATION_TYPE)/ml_dsa_$(PARAMETER_SET)

# --------------------------------------------------------------------
JASMINC ?= jasminc
JASMINCT ?= jasmin-ct

# --------------------------------------------------------------------
IMPLEMENTATION_SOURCES = $(IMPLEMENTATION)/ml_dsa.jazz \
						 $(wildcard $(IMPLEMENTATION)/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/arithmetic/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/encoding/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/sample/*.jinc) \
						 $(wildcard $(COMMON)/*.jinc) \
						 $(wildcard $(COMMON)/arithmetic/*.jinc) \
						 $(wildcard $(COMMON)/encoding/*.jinc) \
						 $(wildcard $(COMMON)/keccak/*.jinc) \
						 $(wildcard $(COMMON)/sample/*.jinc) \
						 $(wildcard $(COMMON)/sample/matrix_A/*.jinc) \
						 $(wildcard $(COMMON)/sample/mask/*.jinc)

OUTPUT_FILE_NAME = ml_dsa_$(PARAMETER_SET)_$(IMPLEMENTATION_TYPE)

$(OUTPUT_FILE_NAME).s: $(IMPLEMENTATION_SOURCES)
	env JASMINPATH="Common=$(COMMON)" $(JASMINC) $(JASMINC_FLAGS) -o $@ $<

# --------------------------------------------------------------------
.PHONY: test
test: $(OUTPUT_FILE_NAME).so
	python3 -m pytest \
		--parameter-set=$(PARAMETER_SET) \
		--implementation-type=$(IMPLEMENTATION_TYPE) \
		tests/

.PHONY: nist-drbg-kat-test
nist-drbg-kat-test: $(OUTPUT_FILE_NAME).so
	python3 -m pytest \
		--parameter-set=$(PARAMETER_SET) \
		--implementation-type=$(IMPLEMENTATION_TYPE) \
		tests/test_nist_drbg_kats.py

$(OUTPUT_FILE_NAME).so: $(OUTPUT_FILE_NAME).s
	$(CC) $^ -fPIC -shared -o $@

.PHONY: check-ct
check-ct: $(IMPLEMENTATION)/ml_dsa.jazz
	env JASMINPATH="Common=$(COMMON)" $(JASMINCT) $^

.PHONY: check-sct
check-sct: $(IMPLEMENTATION)/ml_dsa.jazz
	env JASMINPATH="Common=$(COMMON)" $(JASMINCT) --speculative $^

.PHONY: check-rsb
check-rsb: $(IMPLEMENTATION)/ml_dsa.jazz
	env JASMINPATH="Common=$(COMMON)" $(RSB_CHECKER) --speculative $^

.PHONY: run-interpreter
run-interpreter: $(IMPLEMENTATION)/example.jazz $(IMPLEMENTATION)/ml_dsa.jazz
	$env JASMINPATH="Common=$(COMMON)" (JASMINC) $< | grep 'true'

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
	rm -fr *.s *.so *.o
