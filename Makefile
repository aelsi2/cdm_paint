BUILD_DIR := ./build
PUBLISH_BASE_DIR := ./publish
LOGISIM_DIR := ./logisim
SRC_DIRS := ./src

LOGISIM_PROJECT := $(LOGISIM_DIR)/cdm_paint.circ
CDM_PLUGINS += $(LOGISIM_DIR)/logisim-cdm-emulator-0.2.2.jar
CDM_PLUGINS += $(LOGISIM_DIR)/logisim-banked-memory-0.2.2.jar
TIME_PLUGIN := $(LOGISIM_DIR)/logisim-time-1.1-all.jar
TARGET_IMAGE := $(BUILD_DIR)/cdm_paint.img
COMPILE_COMMANDS := ./compile_commands.json

PUBLISH_ASSETS := $(LOGISIM_PROJECT) $(TARGET_IMAGE) $(CDM_PLUGINS) $(TIME_PLUGIN)
PUBLISH_DIR := $(PUBLISH_BASE_DIR)/cdm_paint
PUBLISH_TAR := $(PUBLISH_BASE_DIR)/cdm_paint.tar.gz
PUBLISH_ZIP := $(PUBLISH_BASE_DIR)/cdm_paint.zip

CDM_PLUGIN_URL := https://github.com/cdm-processors/cdm-devkit/releases/download/0.2.2/cdm-devkit-misc-0.2.2.tar.gz
CC_URL := https://github.com/leadpogrommer/llvm-project-cdm/releases/download/cdm-ver-1.5/clang-cdm-ubuntu-latest.zip
TIME_PLUGIN_URL := https://github.com/aelsi2/logisim_time/releases/download/v1.1/logisim-time-1.1-all.jar
CDM_PLUGIN_ARCHIVE := $(BUILD_DIR)/cdm_devkit.tar.gz
CC_ARCHIVE := $(BUILD_DIR)/clang-cdm.zip

VENV_DIR := $(BUILD_DIR)/.venv
ASM := $(VENV_DIR)/bin/cocas
DOWNLOAD_ASM := $(findstring $(origin ASM),file)

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
ASMS := $(shell find $(SRC_DIRS) -name '*.asm')
C_ASMS := $(SRCS:%=$(BUILD_DIR)/%.asm)
DEPS := $(C_ASMS:.asm=.d)
COMMANDS := $(SRCS:%=$(BUILD_DIR)/%.asm.command)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CFLAGS := $(INC_FLAGS) -MMD -MP -target cdm -O2 -S
CC := $(BUILD_DIR)/clang-cdm
DOWNLOAD_CC := $(findstring $(origin CC),file)

.PHONY: build
build: $(TARGET_IMAGE) $(COMPILE_COMMANDS) $(CDM_PLUGINS) $(TIME_PLUGIN)

$(TARGET_IMAGE): $(ASMS) $(C_ASMS) $(if $(DOWNLOAD_ASM), $(ASM))
	$(ASM) $(filter %.asm,$^) -o $@

$(C_ASMS): $(BUILD_DIR)/%.c.asm: %.c $(if $(DOWNLOAD_CC), $(CC))
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -MJ $@.command

$(COMPILE_COMMANDS): $(COMMANDS)
	rm -f $@
	echo "[" >> $@
	cat $^ | sed "s/,\?\s\+\"--target=cdm\"//g" >> $@
	echo "]" >> $@

$(COMMANDS): %.command: % ;

$(ASM): $(VENV_DIR)
	$(VENV_DIR)/bin/pip3 install cdm-devkit

$(VENV_DIR):
	python3 -m venv $@

$(CDM_PLUGINS): $(CDM_PLUGIN_ARCHIVE)
	tar -xzOf $< jar/$(notdir $@) > $@

$(CDM_PLUGIN_ARCHIVE):
	curl -L $(CDM_PLUGIN_URL) --create-dirs -o $@

$(TIME_PLUGIN):
	curl -L $(TIME_PLUGIN_URL) --create-dirs -o $@

$(CC): $(CC_ARCHIVE)
	bsdtar -xOf $< clang-cdm-ubuntu-latest/clang-19 > $@
	chmod uga+x $@

$(CC_ARCHIVE):
	curl -L $(CC_URL) --create-dirs -o $@

.PHONY: publish
publish: build $(PUBLISH_DIR) $(PUBLISH_ZIP) $(PUBLISH_TAR) 

$(PUBLISH_ZIP): $(PUBLISH_DIR)
	bsdtar -C $(dir $<) --format zip -cf $@ $(notdir $<)

$(PUBLISH_TAR): $(PUBLISH_DIR)
	tar -C $(dir $<) -czf $@ $(notdir $<)

$(PUBLISH_DIR): $(PUBLISH_ASSETS)
	mkdir -p $@
	cp $^ $@
	sed -i 's/"[^"]*\($(notdir $(TARGET_IMAGE))\)"/"\1"/g' $@/$(notdir $(LOGISIM_PROJECT))

.PHONY: clean
clean:
	rm -f $(COMPILE_COMMANDS)
	rm -rf $(BUILD_DIR)
	rm -rf $(PUBLISH_BASE_DIR)
	rm -f $(LOGISIM_DIR)/*.jar

-include $(DEPS)
