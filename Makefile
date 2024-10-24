TOP = /home/efgh/repos/formosa-mldsa

PARAMETER_SET = 65
IMPLEMENTATION_TYPE = ref
# --------------------------------------------------------------------
JASMINC ?= jasminc
JASMIN_COMMAND ?= $(JASMINC) $(JASMINC_FLAGS) $(INCLUDE)

# --------------------------------------------------------------------
IMPLEMENTATION = $(TOP)/ml_dsa_$(PARAMETER_SET)/$(IMPLEMENTATION_TYPE)

IMPLEMENTATION_SOURCES = $(IMPLEMENTATION)/ml_dsa.jazz \
						 $(wildcard $(IMPLEMENTATION)/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/encoding/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/sample/*.jinc) \
						 $(wildcard $(IMPLEMENTATION)/arithmetic/*.jinc)

OUTPUT_FILE_NAME = ml_dsa_$(PARAMETER_SET)_$(IMPLEMENTATION_TYPE)

$(OUTPUT_FILE_NAME).s: $(IMPLEMENTATION_SOURCES)
	$(JASMIN_COMMAND) -o $@ $<

# --------------------------------------------------------------------
.PHONY: test
test: $(OUTPUT_FILE_NAME).so
	cd test && \
		python3 nist_drbg_kat_tests.py && \
		python3 nist_acvp_tests.py && \
		python3 wycheproof_verify_tests.py && \
		python3 wycheproof_sign_tests.py

$(OUTPUT_FILE_NAME).so: $(OUTPUT_FILE_NAME).s
	$(CC) $^ -fPIC -shared -o $@

# --------------------------------------------------------------------
ml_dsa_$(PARAMETER_SET)_$(IMPLEMENTATION_TYPE)_bench.o: $(OUTPUT_FILE_NAME).s bench/bench.c
	$(CC) -DVERIFICATION_KEY_SIZE=1952 \
		  -DSIGNING_KEY_SIZE=4032 \
		  -DSIGNATURE_SIZE=3309 \
		  $^ -o $@

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr \
		$(TOP)/*.s \
		$(TOP)/*.so
