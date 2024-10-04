TOP = /home/efgh/repos/formosa-mldsa
SRC = $(TOP)/src
# --------------------------------------------------------------------
SRCS_TOP = $(SRC)/ml_dsa_65/ref
SRCS = $(SRCS_TOP)/sign.jazz

# --------------------------------------------------------------------
override FLAGS += -noinsertarraycopy -lazy-regalloc
INCLUDE = -I Common:$(SRC)/common
JASMINC ?= jasminc
JASMIN_COMMAND ?= $(JASMINC) $(FLAGS) $(INCLUDE)

# --------------------------------------------------------------------
generate-assembly: $(SRCS:%.jazz=%.s)
%.s: %.jazz
	$(JASMIN_COMMAND) -o $@ $<

# --------------------------------------------------------------------
CFLAGS=-Wall -Wextra -Wpedantic -Werror -Wmissing-prototypes
test/generate_keypair.o: test/generate_keypair.c $(SRCS_TOP)/sign.s test/randombytes.c
	$(CC) $(CFLAGS) -I$(SRCS_TOP)/include \
		-DVERIFICATION_KEY_BYTES=1952 \
		-DSIGNING_KEY_BYTES=4000 \
		-DRANDOMNESS_BYTES=32 \
		-DGENERATE_KEYPAIR_DERAND=jade_sign_dilithium_dilithium3_amd64_ref_keypair_derand \
		$^ -o $@

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr $(SRCS_TOP)/*.s $(TOP)/test/*.o
