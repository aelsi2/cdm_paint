BUILD_DIR := ./build
SRC_DIRS := ./src
VENV_DIR := $(BUILD_DIR)/.venv
TARGET_IMAGE := $(BUILD_DIR)/cdm_paint.img

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
ASMS := $(shell find $(SRC_DIRS) -name '*.s')

IRS := $(SRCS:%=$(BUILD_DIR)/%.ll)
C_ASMS := $(SRCS:%=$(BUILD_DIR)/%.s)
DEPS := $(IRS:.ll=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS) -MMD -MP -target cdm -O2 -S -emit-llvm
CC := clang-cdm
SC := llc-cdm

.PHONY: all
all: $(TARGET_IMAGE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

$(TARGET_IMAGE): $(ASMS) $(C_ASMS) $(VENV_DIR)/bin/cocas
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

-include $(DEPS)
