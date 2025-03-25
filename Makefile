BUILD_DIR := ./build
SRC_DIRS := ./src
VENV_DIR := $(BUILD_DIR)/.venv
TARGET_IMAGE := $(BUILD_DIR)/cdm_paint.img
COMPILE_COMMANDS := compile_commands.json

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
ASMS := $(shell find $(SRC_DIRS) -name '*.asm')

IRS := $(SRCS:%=$(BUILD_DIR)/%.ll)
C_ASMS := $(SRCS:%=$(BUILD_DIR)/%.asm)
DEPS := $(IRS:.ll=.d)
COMMANDS := $(SRCS:%=$(BUILD_DIR)/%.ll.command)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS) -MMD -MP -target cdm -O2 -S -emit-llvm
CC := clang-cdm
SC := llc-cdm

.PHONY: all
all: $(TARGET_IMAGE) $(COMPILE_COMMANDS)

.PHONY: clean
clean:
	rm -f $(COMPILE_COMMANDS)
	rm -rf $(BUILD_DIR)

$(TARGET_IMAGE): $(ASMS) $(C_ASMS) $(VENV_DIR)/bin/cocas
	$(VENV_DIR)/bin/cocas $(filter %.asm,$^) -o $@

$(C_ASMS): %.c.asm: %.c.ll
	$(SC) -march=cdm $< -o $@

$(IRS): $(BUILD_DIR)/%.c.ll: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -MJ $@.command

$(COMPILE_COMMANDS): $(COMMANDS)
	rm -f $(COMPILE_COMMANDS)
	echo "[" >> $@
	cat $^ | sed "s/,\?\s\+\"--target=cdm\"//g" >> $@
	echo "]" >> $@

$(COMMANDS): %.command: % ;

$(VENV_DIR)/bin/cocas: $(VENV_DIR)
	$(VENV_DIR)/bin/pip3 install cdm-devkit

$(VENV_DIR):
	python3 -m venv $@

-include $(DEPS)
