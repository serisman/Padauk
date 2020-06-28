# Name: Makefile
# Project: Padauk/projects/7-seg-clock
# Author: Stephen Erisman <github@serisman.com>
# Creation Date: 2020-06-25
# License: MIT

# ---------------------------------------------------------------------

#DEVICE = PMS152
DEVICE = PFS154
#DEVICE = PFS173
#F_CPU = 65536
F_CPU = 524288
TARGET_VDD_MV = 3300
TARGET_VDD = 3.3
#DEBUG = 1

# ---------------------------------------------------------------------

ifeq ($(DEVICE), PMS152)
	ARCH = pdk14
else ifeq ($(DEVICE), PFS154)
	ARCH = pdk14
else ifeq ($(DEVICE), PFS173)
	ARCH = pdk15
endif

DEBUG ?= 0

ROOT_DIR = ../..
BUILD_DIR = .build

LIB_SOURCES = $(wildcard $(ROOT_DIR)/lib/*.c) $(wildcard $(ROOT_DIR)/lib/**/*.c)
LIB_OBJECTS = $(patsubst $(ROOT_DIR)/lib/%.c,$(BUILD_DIR)/lib/%.rel,$(LIB_SOURCES))

SOURCES = main.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.rel,$(SOURCES))

# http://sdcc.sourceforge.net/doc/sdccman.pdf
COMPILE = sdcc -m$(ARCH) -c --std-sdcc11 --opt-code-size -D$(DEVICE) -DF_CPU=$(F_CPU) -DTARGET_VDD_MV=$(TARGET_VDD_MV) -DDEBUG=$(DEBUG) -I. -I$(ROOT_DIR)/include
BUILD_LIB = sdar -rc
LINK = sdcc -m$(ARCH)
EASYPDKPROG = easypdkprog

# symbolic targets:
all: size

print-%: ; @echo $* = $($*)

$(BUILD_DIR)/%.rel: %.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib/%.rel: $(ROOT_DIR)/lib/%.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib.lib: $(LIB_OBJECTS)
	$(BUILD_LIB) $@ $(LIB_OBJECTS)

$(BUILD_DIR)/rom.ihx: $(OBJECTS) $(BUILD_DIR)/lib.lib
	@mkdir -p $(dir $(BUILD_DIR))
	$(LINK) --out-fmt-ihx -o $(BUILD_DIR)/rom.ihx $(OBJECTS) $(BUILD_DIR)/lib.lib

rom.hex: $(BUILD_DIR)/rom.ihx
	packihx $(BUILD_DIR)/rom.ihx > rom.hex

rom.bin: $(BUILD_DIR)/rom.ihx
	makebin -p $(BUILD_DIR)/rom.ihx rom.bin

size: rom.bin
	@echo '---------- Segments ----------'
	@egrep '(ABS,CON)|(REL,CON)' $(BUILD_DIR)/rom.map | gawk --non-decimal-data '{dec = sprintf("%d","0x" $$2); print dec " " $$0}' | /usr/bin/sort -n -k1 | cut -f2- -d' '
	@echo '------------------------------'
	@stat -L --printf "Size of rom.bin: %s bytes\n" rom.bin

program: size
	$(EASYPDKPROG) -n $(DEVICE) write $(BUILD_DIR)/rom.ihx

run:
	$(EASYPDKPROG) -n $(DEVICE) -r $(TARGET_VDD)) start

clean:
	rm -r -f $(BUILD_DIR)
