TARGET_IMAGE := cdm_paint.img

SRC_DIRS := ./src
SRCS := $(shell find $(SRC_DIRS) -name '*.c')
ASMS := $(shell find $(SRC_DIRS) -name '*.s')

BUILD_DIR := ./build
VENV_DIR := $(BUILD_DIR)/.venv

IRS := $(SRCS:%=$(BUILD_DIR)/%.ll)
C_ASMS := $(SRCS:%=$(BUILD_DIR)/%.s)

DEPS := $(IRS:.ll=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS) -MMD -MP -target cdm -O2 -S -emit-llvm
CC := clang-cdm
SC := llc-cdm

$(BUILD_DIR)/$(TARGET_IMAGE): $(ASMS) $(C_ASMS) $(VENV_DIR)/bin/cocas
	$(VENV_DIR)/bin/cocas $(filter %.s,$^) $(ENTRY_POINT) -o $@

$(C_ASMS): %.c.s: %.c.ll
	$(SC) -march=cdm $< -o $@

$(IRS): $(BUILD_DIR)/%.c.ll: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(VENV_DIR)/bin/cocas: $(VENV_DIR)
	$(VENV_DIR)/bin/pip3 install cdm-devkit

$(VENV_DIR):
	python3 -m venv $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
