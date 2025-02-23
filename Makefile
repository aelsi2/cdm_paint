TARGET_IMAGE := cdm_paint.img

ENTRY_POINT := ./src/main.s

SRC_DIRS := ./src
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

BUILD_DIR := ./build
VENV_DIR := $(BUILD_DIR)/.venv

OBJS := $(SRCS:%=$(BUILD_DIR)/%.ll)
ASMS := $(SRCS:%=$(BUILD_DIR)/%.s)

DEPS := $(OBJS:.ll=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS) -MMD -MP -target cdm -O2 -S -emit-llvm
CC := ./llvm-project-cdm/build/bin/clang

$(BUILD_DIR)/$(TARGET_IMAGE): $(ASMS) $(VENV_DIR)/bin/cocas
	$(VENV_DIR)/bin/cocas $(filter %.s,$^) $(ENTRY_POINT) -o $@

$(ASMS): %.c.s: %.c.ll
	./llvm-project-cdm/build/bin/llc -march=cdm $< -o $@

$(OBJS): $(BUILD_DIR)/%.c.ll: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(VENV_DIR)/bin/cocas: $(VENV_DIR)
	$(VENV_DIR)/bin/pip install cdm-devkit

$(VENV_DIR):
	python -m venv $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
