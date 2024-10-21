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
	cd test && python3 test_nist_drbg_kats.py

$(OUTPUT_FILE_NAME).so: $(OUTPUT_FILE_NAME).s
	$(CC) $^ -fPIC -shared -o $@

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr \
		$(TOP)/*.s \
		$(TOP)/*.so
