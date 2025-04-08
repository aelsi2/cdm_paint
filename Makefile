BUILD_DIR := ./build
LOGISIM_DIR := ./logisim
SRC_DIRS := ./src
VENV_DIR := $(BUILD_DIR)/.venv
TARGET_IMAGE := $(BUILD_DIR)/cdm_paint.img
COMPILE_COMMANDS := compile_commands.json
LOGISIM_PLUGINS += $(LOGISIM_DIR)/logisim-cdm-emulator-0.2.2.jar
LOGISIM_PLUGINS += $(LOGISIM_DIR)/logisim-banked-memory-0.2.2.jar

LOGISIM_PLUGIN_URL := https://github.com/cdm-processors/cdm-devkit/releases/download/0.2.2/cdm-devkit-misc-0.2.2.tar.gz
CC_URL := https://github.com/leadpogrommer/llvm-project-cdm/releases/download/cdm-ver-1.5/clang-cdm-ubuntu-latest.zip

LOGISIM_PLUGIN_ARCHIVE := $(BUILD_DIR)/cdm_devkit.tar.gz
CC_ARCHIVE := $(BUILD_DIR)/clang-cdm.zip

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
ASMS := $(shell find $(SRC_DIRS) -name '*.asm')

C_ASMS := $(SRCS:%=$(BUILD_DIR)/%.asm)
DEPS := $(C_ASMS:.asm=.d)
COMMANDS := $(SRCS:%=$(BUILD_DIR)/%.asm.command)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS) -MMD -MP -target cdm -O2 -S
CC := $(BUILD_DIR)/clang-cdm

.PHONY: all
all: $(TARGET_IMAGE) $(COMPILE_COMMANDS) $(LOGISIM_PLUGINS)

.PHONY: clean
clean:
	rm -f $(COMPILE_COMMANDS)
	rm -rf $(BUILD_DIR)
	rm -f $(LOGISIM_DIR)/*.jar

$(TARGET_IMAGE): $(ASMS) $(C_ASMS) $(VENV_DIR)/bin/cocas
	$(VENV_DIR)/bin/cocas $(filter %.asm,$^) -o $@

$(C_ASMS): $(BUILD_DIR)/%.c.asm: %.c $(CC)
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

$(LOGISIM_PLUGINS): $(LOGISIM_PLUGIN_ARCHIVE)
	tar -xzOf $^ jar/$(notdir $@) > $@

$(LOGISIM_PLUGIN_ARCHIVE):
	curl -L $(LOGISIM_PLUGIN_URL) --create-dirs -o $@

$(CC): $(CC_ARCHIVE)
	bsdtar -xOf $^ clang-cdm-ubuntu-latest/clang-19 > $@
	chmod uga+x $@

$(CC_ARCHIVE):
	curl -L $(CC_URL) --create-dirs -o $@

-include $(DEPS)
