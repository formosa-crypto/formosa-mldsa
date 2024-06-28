#--
ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7

#-mcpu=cortex-m4 # not working - TODO: check why

# Variables
INCLUDES := -I../../test/common -I../../

LIB_C = ../../libdilithium5_c.a
LDFLAGS_C = -L../.. -ldilithium5_c

# Source files
SRC_C = main_c.c
OBJ_C = $(SRC_C:.c=.o)

# Target executable
TARGET_C = bench_sign_keypair

# Rules
all: $(TARGET_C)

$(TARGET_C): $(OBJ_C) $(LIB_C)
	$(ARMCC) $(ARMCFLAGS) -static -o $@ $(OBJ_C) $(LDFLAGS_C)

%.o: %.c
	$(ARMCC) $(ARMCFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJ_C) $(TARGET_C)

.PHONY: all clean
