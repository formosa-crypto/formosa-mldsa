#-------------------------------------------------------------------------------

include ../../ml-dsa-any/common.mk

#-------------------------------------------------------------------------------

arch = arm-m4

JASMIN_LIB := libml-dsa-65_jasmin_test_$(arch).a
JASMIN_OBJECTS := library_test_$(arch).o
JASMIN_FILES := library_test_$(arch).jazz

ASM_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.s)

$(ASM_JASMIN_FILES):
%.s: %.jazz
	$(JASMINC) -arch=$(arch) -o $@ $<
