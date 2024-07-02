#--
ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7
ARMAR ?= arm-linux-gnueabi-ar

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	ARMCC := /Applications/ARM/bin/arm-none-eabi-gcc
	ARMCFLAGS := -Wall -O1 -fPIC -mcpu=cortex-m4 -mlittle-endian -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
	ARMAR := /Applications/ARM/bin/arm-none-eabi-ar
endif

#--
TESTS_C := $(subst ./,,$(shell find . -name 'test_*.c'))
TESTS_BIN := $(subst .c,, $(TESTS_C))
TESTS_OUT := $(addsuffix .out, $(TESTS_BIN))

#-- 
default:
	$(MAKE) clean
	$(MAKE) -C ../ small-testing
	$(MAKE) compile
	$(MAKE) run

compile: $(TESTS_BIN)
run: $(TESTS_OUT)

%.out: %
	./$< || true # TODO: remove this for CI to fail || keep track of individual failures (this: when there is some time)

# TODO: note that the following dependency list is incomplete
$(TESTS_BIN):
test_%: test_%.c ../%.jinc ../%.jazz
	$(ARMCC) -o $@ $(ARMCFLAGS) -static test_$*.c -I./common -I../ -L../ -ldilithium5_clean

#--
TEST_NAMESPACE := -DJADE_NAMESPACE=JADE_SIGN_dilithium_dilithium5_armv7m_clean -DJADE_NAMESPACE_LC=jade_sign_dilithium_dilithium5_armv7m_clean
TEST_SRC := common/dilithium5_api.c common/notrandombytes.c common/print.c
TEST_INCLUDE := -I./common -I../
TEST_LINKER := -L../ -ldilithium5_clean

.PHONY: checksumbig checksumsmall functest

checksumbig:
	$(MAKE) -C ../ small-testing # temp
	$(ARMCC) $(ARMCFLAGS) -static -o $@ $(TEST_NAMESPACE) common/checksumbig.c $(TEST_SRC) $(TEST_INCLUDE) $(TEST_LINKER)

checksumsmall:
	$(MAKE) -C ../ small-testing #temp
	$(ARMCC) $(ARMCFLAGS) -static -o $@ $(TEST_NAMESPACE) common/checksumsmall.c $(TEST_SRC) $(TEST_INCLUDE) $(TEST_LINKER)

functest:
	$(MAKE) -C ../ small-testing # temp
	$(ARMCC) $(ARMCFLAGS) -static -o $@ $(TEST_NAMESPACE) common/functest.c $(TEST_SRC) $(TEST_INCLUDE) $(TEST_LINKER)

#--
.PHONY: clean
clean:
	rm -f $(TESTS_BIN) $(TESTS_OUT) checksumbig checksumsmall functest

