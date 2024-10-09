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
test/ml_dsa.so: $(SRCS_TOP)/sign.s
	$(CC) $(CFLAGS) -I$(SRCS_TOP)/include \
		$^ -fPIC -shared -o $@

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr \
		$(SRCS_TOP)/*.s \
		$(TOP)/test/*.o \
		$(TOP)/test/*.so
