ARCHITECTURE ?= arm-m4
PARAMETER_SET ?= 65
IMPLEMENTATION_TYPE ?= ref

COMMON = $(ARCHITECTURE)/$(IMPLEMENTATION_TYPE)/common
IMPLEMENTATION = $(ARCHITECTURE)/$(IMPLEMENTATION_TYPE)/ml_dsa_$(PARAMETER_SET)

JASMINC ?= jasminc
JASMINCT ?= jasmin-ct

# --------------------------------------------------------------------
#  Assembly generation
# --------------------------------------------------------------------
IMPLEMENTATION_SOURCES = $(shell find $(IMPLEMENTATION)/ -type f -name '*.jinc') \
                         $(shell find $(COMMON)/ -type f -name '*.jinc')

OUTPUT_FILE_NAME = ml_dsa_$(PARAMETER_SET)_$(IMPLEMENTATION_TYPE)_$(ARCHITECTURE)

$(OUTPUT_FILE_NAME).s: $(IMPLEMENTATION)/ml_dsa.jazz $(IMPLEMENTATION_SOURCES)
	env JASMINPATH="Common=$(COMMON)" $(JASMINC) -arch=$(ARCHITECTURE) $(JASMINC_FLAGS) -o $@ $<

# --------------------------------------------------------------------
#  KAT testing and safety checking
# --------------------------------------------------------------------
# For x86-64: Generate a shared-library to pass to ctypes.
$(OUTPUT_FILE_NAME).so: $(OUTPUT_FILE_NAME).s
	$(CC) $^ -fPIC -shared -o $@

# For ARM-M4: Generate a cross-compiled executable to be called by python.
CROSS_COMPILER ?= arm-none-linux-gnueabihf-gcc
$(OUTPUT_FILE_NAME).o: arm-m4/wrapper.c $(OUTPUT_FILE_NAME).s
	$(CROSS_COMPILER) -Wall -I$(IMPLEMENTATION) $^ -o $@ -no-pie

TESTING_WRAPPER :=
ifeq ($(ARCHITECTURE), x86-64)
	TESTING_WRAPPER = $(OUTPUT_FILE_NAME).so
else
	TESTING_WRAPPER = $(OUTPUT_FILE_NAME).o
endif

.PHONY: test
test: $(TESTING_WRAPPER)
	python3 -m pytest \
		--parameter-set=$(PARAMETER_SET) \
		--architecture=$(ARCHITECTURE) \
		--implementation-type=$(IMPLEMENTATION_TYPE) \
		tests/

.PHONY: nist-drbg-kat-test
nist-drbg-kat-test: $(TESTING_WRAPPER)
	python3 -m pytest \
		--parameter-set=$(PARAMETER_SET) \
		--architecture=$(ARCHITECTURE) \
		--implementation-type=$(IMPLEMENTATION_TYPE) \
		tests/test_nist_drbg_kats.py

.PHONY: run-interpreter
run-interpreter: $(IMPLEMENTATION)/example.jazz $(IMPLEMENTATION)/ml_dsa.jazz
	env JASMINPATH="Common=$(COMMON)" $(JASMINC) -arch=$(ARCHITECTURE) $< | grep 'true'

# --------------------------------------------------------------------
#  CT and SCT checking
# --------------------------------------------------------------------
.PHONY: check-ct
check-ct: $(IMPLEMENTATION)/ml_dsa.jazz
	env JASMINPATH="Common=$(COMMON)" $(JASMINCT) --arch=$(ARCHITECTURE) --doit $(JASMINCT_FLAGS) $^

.PHONY: check-sct
check-sct: $(IMPLEMENTATION)/ml_dsa.jazz
	env JASMINPATH="Common=$(COMMON)" $(JASMINCT) $(JASMINCT_FLAGS) --speculative $^

# --------------------------------------------------------------------
#  Benchmarking
# --------------------------------------------------------------------
bench_jasmin.o: $(OUTPUT_FILE_NAME).s bench/bench_jasmin.c bench/notrandombytes.c $(IMPLEMENTATION)/api.h
	$(CC) -Wall -Werror \
		  -DIMPLEMENTATION_TYPE=$(IMPLEMENTATION_TYPE) \
		  -DKEYGEN=ml_dsa_$(PARAMETER_SET)_keygen \
		  -DSIGN=ml_dsa_$(PARAMETER_SET)_sign \
		  -DVERIFY=ml_dsa_$(PARAMETER_SET)_verify \
		  $^ -I $(IMPLEMENTATION) -o $@

bench_pqclean_65_avx2.o: bench/bench_pqclean_65_avx2.c bench/notrandombytes.c bench/pqclean_ml_dsa_65_avx2/libml-dsa-65_avx2.a fips202.o
	$(CC) -Wall -Werror $^ -o $@

fips202.o: bench/pqclean_ml_dsa_65_avx2/fips202.c
	$(CC) -Wall -Werror $< -c -o $@

bench/pqclean_ml_dsa_65_avx2/libml-dsa-65_avx2.a:
	$(MAKE) -C bench/pqclean_ml_dsa_65_avx2

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr *.s *.so *.o *.core
