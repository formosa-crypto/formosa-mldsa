ARCHITECTURE ?= x86-64
PARAMETER_SET ?= 65
IMPLEMENTATION_TYPE ?= avx2

ROOT_DIR := ..
MLDSA_NATIVE_DIR := mldsa-native
MLDSA_NATIVE_ROOT := $(MLDSA_NATIVE_DIR)/mldsa
MLDSA_NATIVE_LIBRARY := $(MLDSA_NATIVE_DIR)/test/build/libmldsa65.a

COMMON = $(ROOT_DIR)/$(ARCHITECTURE)/$(IMPLEMENTATION_TYPE)/common
IMPLEMENTATION = $(ROOT_DIR)/$(ARCHITECTURE)/$(IMPLEMENTATION_TYPE)/ml_dsa_$(PARAMETER_SET)
OUTPUT_FILE_NAME = $(ROOT_DIR)/ml_dsa_$(PARAMETER_SET)_$(IMPLEMENTATION_TYPE)_$(ARCHITECTURE)

.PHONY: all clean compare_performance

all: bench_jasmin bench_mldsa_native_65

$(OUTPUT_FILE_NAME).s:
	$(MAKE) -C $(ROOT_DIR) \
		ARCHITECTURE=$(ARCHITECTURE) \
		PARAMETER_SET=$(PARAMETER_SET) \
		IMPLEMENTATION_TYPE=$(IMPLEMENTATION_TYPE) \
		$(notdir $@)

bench_jasmin: $(OUTPUT_FILE_NAME).s bench_jasmin.c bench_common.c notrandombytes.c $(IMPLEMENTATION)/api.h
	$(CC) -Wall -Werror \
		-DIMPLEMENTATION_TYPE=$(IMPLEMENTATION_TYPE) \
		-DKEYGEN=ml_dsa_$(PARAMETER_SET)_keygen \
		-DSIGN=ml_dsa_$(PARAMETER_SET)_sign \
		-DVERIFY=ml_dsa_$(PARAMETER_SET)_verify \
		$(OUTPUT_FILE_NAME).s bench_jasmin.c notrandombytes.c \
		-I $(IMPLEMENTATION) -o $@

$(MLDSA_NATIVE_LIBRARY):
	$(MAKE) -C $(MLDSA_NATIVE_DIR) OPT=1 AUTO=1 $(patsubst $(MLDSA_NATIVE_DIR)/%,%,$@)

bench_mldsa_native_65: bench_mldsa_native_65.c bench_common.c notrandombytes.c $(MLDSA_NATIVE_LIBRARY)
	$(CC) -Wall -Werror -I$(MLDSA_NATIVE_ROOT) \
		bench_mldsa_native_65.c notrandombytes.c $(MLDSA_NATIVE_LIBRARY) -o $@

clean:
	$(MAKE) -C $(MLDSA_NATIVE_DIR) clean
	rm -rf bench_jasmin bench_mldsa_native_65

compare_performance:
	python3 compare_performance.py $(if $(MARKDOWN),--markdown,) $(if $(COLOR),--color $(COLOR),)
