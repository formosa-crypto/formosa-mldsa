#-------------------------------------------------------------------------------
include ../ml-dsa-any/common.mk

#-------------------------------------------------------------------------------

all: clean compile

#-------------------------------------------------------------------------------

JASMIN_LIB := libml-dsa-65_jasmin_$(arch).a
JASMIN_OBJECTS := library_export_$(arch).o
JASMIN_FILES := library_export_$(arch).jazz

PRE_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.jpp)
ASM_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%.s)
OBJ_JASMIN_FILES := $(JASMIN_FILES:%.jazz=%_jazz.o)

#-------------------------------------------------------------------------------

$(JASMIN_OBJECTS): library_export_$(arch).s
	$(CC) $(CFLAGS) -c -o $@ $<

$(ASM_JASMIN_FILES):
%.s: %.jazz
	$(JASMINC) -arch=$(arch) -o $@ $<

#-------------------------------------------------------------------------------

compile: $(JASMIN_LIB)

$(JASMIN_LIB): $(JASMIN_OBJECTS)
	$(AR) -r $@ $(JASMIN_OBJECTS)

#-------------------------------------------------------------------------------
clean:
	$(RM) $(JASMIN_LIB)
	$(RM) $(JASMIN_OBJECTS)
	$(RM) $(ASM_JASMIN_FILES)
	$(RM) $(PRE_JASMIN_FILES)
	$(RM) $(OBJ_JASMIN_FILES)
	$(RM) library_$(arch).{o,s}
