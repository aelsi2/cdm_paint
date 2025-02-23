TARGET_IMAGE := cdm_paint.img

ENTRY_POINT := ./src/main.s

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.ll)
ASMS := $(SRCS:%=$(BUILD_DIR)/%.s)

DEPS := $(OBJS:.ll=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(TARGET_IMAGE): $(ASMS)
	./.venv/bin/cocas $^ $(ENTRY_POINT) -o $@

$(ASMS): %.c.s: %.c.ll
	./llvm-project-cdm/build/bin/llc -march=cdm $< -o $@

$(OBJS): $(BUILD_DIR)/%.c.ll: %.c
	mkdir -p $(dir $@)
	./llvm-project-cdm/build/bin/clang -target cdm -O2 -S -emit-llvm $< -o $@ -MMD -MP

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
