TOP = /home/efgh/repos/formosa-mldsa
IMPLEMENTATION = $(TOP)/ml_dsa_65/ref

# --------------------------------------------------------------------
override FLAGS += -noinsertarraycopy -lazy-regalloc
JASMINC ?= jasminc
JASMIN_COMMAND ?= $(JASMINC) $(FLAGS) $(INCLUDE)

# --------------------------------------------------------------------
ml_dsa.s: $(IMPLEMENTATION)/ml_dsa.jazz $(wildcard $(IMPLEMENTATION)/*.jinc)
	$(JASMIN_COMMAND) -o $@ $<

# --------------------------------------------------------------------
.PHONY: test
test: test/ml_dsa.so
	python3 test/nistkat.py

test/ml_dsa.so: ml_dsa.s
	$(CC) $^ -fPIC -shared -o $@

# --------------------------------------------------------------------
.PHONY: clean
clean:
	rm -fr \
		$(IMPLEMENTATION)/*.s \
		$(TOP)/test/*.o \
		$(TOP)/test/*.so
