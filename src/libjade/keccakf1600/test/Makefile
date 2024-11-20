#-------------------------------------------------------------------------------

include ../../ml-dsa-any/common.mk


# NOTES:
# - after clone: git submodule init && git submodule update (this test needs libjade code)
# - JASMINC must be set to 'https://github.com/jasmin-lang/jasmin/pull/921'
# - keccakf1600_armv7m_pqm4.s is marked as phony bc the dependencies of that file are not being tracked
# - the expected output of make is the following
# ```
# arm-linux-gnueabi-gcc -Wall -march=armv7 -DTESTS=1000000 -o test test.c keccakf1600_armv7m_pqm4.s
# qemu-arm -L /usr/arm-linux-gnueabi/ ./test
# 0a3cbe74 1db40d45 12000be8 ac056265 28fba4e6 1a893aea 80ef5875 476ee37e 88b45ef9 d906ac94 
# 93ab97d5 5c29be6a 22e997e6 d3a1b99a 9b4c61aa d14a7d90 9ea6d1e5 8be59854 78a2c8a6 2f284da8 
# 045e5902 409db7f5 3b79dae2 f712de78 c3b65b45 60c61792 b850e5a9 cad504cc b07a6418 794f5a03 
# 08aedb0e 4cee3302 98b52a49 501029d8 b2f48114 bf77dc6d 54a5d94e 48b9db79 7acbfdf3 14df442c 
# fe1c7639 de0044dc 025daa12 1280e446 b95eb440 257ae8e6 ab870f87 50a497a6 6e3585e4 271e0f71 
#
#OK
#

TESTS ?=1000000

#--

RUN ?=$(QEMU)

#--

.PHONY: run keccakf1600_armv7m_pqm4.s

default: run

run: test
	$(RUN) ./$<

test: test.c keccakf1600_armv7m_pqm4.s
	$(CC) $(CFLAGS) -DTESTS=$(TESTS) -o $@ $^

keccakf1600_armv7m_pqm4.s: ../keccakf1600_pqm4.jazz
	$(JASMINC) -arch arm-m4 -o $@ $<

#--

clean:
	rm -f test
	rm -f keccakf1600_armv7m_pqm4.s
