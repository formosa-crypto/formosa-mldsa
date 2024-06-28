#--
ARMCC ?= arm-linux-gnueabi-gcc
ARMCFLAGS ?= -Wall -O3 -march=armv7

#-mcpu=cortex-m4 # not working - TODO: check why

# Variables
INCLUDES := -I../../test/common -I../../

LIB_J = ../../libdilithium5_j.a
LDFLAGS_J = -L../.. -ldilithium5_j

# Source files
SRC_J = main_j.c
OBJ_J = $(SRC_J:.c=.o)

# Target executable
TARGET_J = bench_sign_keypair_jazz

# Rules
all: $(TARGET_J)

$(TARGET_J): $(OBJ_J) $(LIB_J)
	$(ARMCC) $(ARMCFLAGS) -static -o $@ $(OBJ_J) $(LDFLAGS_J)

%.o: %.c
	$(ARMCC) $(ARMCFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJ_J) $(TARGET_J)

.PHONY: all clean
