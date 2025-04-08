BUILD_DIR := ./build
LOGISIM_DIR := ./logisim
SRC_DIRS := ./src
VENV_DIR := $(BUILD_DIR)/.venv
TARGET_IMAGE := $(BUILD_DIR)/cdm_paint.img
COMPILE_COMMANDS := compile_commands.json

LOGISIM_PLUGINS := logisim-cdm-emulator-0.2.2.jar logisim-banked-memory-0.2.2.jar
LOGISIM_PLUGIN_URL := https://github.com/cdm-processors/cdm-devkit/releases/download/0.2.2/cdm-devkit-misc-0.2.2.tar.gz

LOGISIM_PLUGIN_FILES := $(addprefix $(LOGISIM_DIR)/,$(LOGISIM_PLUGINS))
LOGISIM_PLUGIN_ARCHIVE := $(BUILD_DIR)/cdm_devkit.tar.gz

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
LLC := llc-cdm

.PHONY: all
all: $(TARGET_IMAGE) $(COMPILE_COMMANDS) $(LOGISIM_PLUGIN_FILES)

.PHONY: clean
clean:
	rm -f $(COMPILE_COMMANDS)
	rm -rf $(BUILD_DIR)
	rm -f $(LOGISIM_DIR)/*.jar

$(TARGET_IMAGE): $(ASMS) $(C_ASMS) $(VENV_DIR)/bin/cocas
	$(VENV_DIR)/bin/cocas $(filter %.asm,$^) -o $@

$(C_ASMS): %.c.asm: %.c.ll
	$(LLC) -march=cdm $< -o $@

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

$(LOGISIM_PLUGIN_FILES): $(LOGISIM_PLUGIN_ARCHIVE)
	tar -xzOf $^ jar/$(notdir $@) > $@

$(LOGISIM_PLUGIN_ARCHIVE):
	curl -L $(LOGISIM_PLUGIN_URL) -o $@

-include $(DEPS)
