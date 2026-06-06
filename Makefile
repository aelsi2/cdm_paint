BUILD_DIR := ./build
DIST_BASE_DIR := ./dist
LOGISIM_DIR := ./logisim
SRC_DIRS := ./src
LINKER_SCRIPT = ./memory.x

LOGISIM_PROJECT := $(LOGISIM_DIR)/cdm_paint.circ
CDM_PLUGINS += $(LOGISIM_DIR)/logisim-cdm-emulator-0.2.2.jar
CDM_PLUGINS += $(LOGISIM_DIR)/logisim-banked-memory-0.2.2.jar
TIME_PLUGIN := $(LOGISIM_DIR)/logisim-time-1.1-all.jar
TARGET_IMAGE := $(BUILD_DIR)/cdm_paint.img
COMPILE_COMMANDS := ./compile_commands.json

DIST_ASSETS := $(LOGISIM_PROJECT) $(TARGET_IMAGE) $(CDM_PLUGINS) $(TIME_PLUGIN)
DIST_DIR := $(DIST_BASE_DIR)/cdm_paint
DIST_TAR := $(DIST_BASE_DIR)/cdm_paint.tar.gz
DIST_ZIP := $(DIST_BASE_DIR)/cdm_paint.zip

CDM_PLUGIN_URL := https://github.com/cdm-processors/cdm-devkit/releases/download/0.2.2/cdm-devkit-misc-0.2.2.tar.gz
TIME_PLUGIN_URL := https://github.com/aelsi2/logisim_time/releases/download/v1.1/logisim-time-1.1-all.jar

TARGET_BINARY = $(basename $(TARGET_IMAGE)).elf
C_SOURCES := $(shell find $(SRC_DIRS) -name '*.c')
C_OBJECTS := $(C_SOURCES:%=$(BUILD_DIR)/%.o)
COMMANDS := $(C_SOURCES:%=$(BUILD_DIR)/%.o.command)

CC := clang-cdm
INC_FLAGS := $(addprefix -I,$(shell find $(SRC_DIRS) -type d))
CFLAGS := -ffreestanding -O2 -MMD -MP $(INC_FLAGS) --target=cdm -mmem-model=harvard

.PHONY: all
all: $(TARGET_IMAGE) $(COMPILE_COMMANDS) $(CDM_PLUGINS) $(TIME_PLUGIN)

$(TARGET_IMAGE): $(TARGET_BINARY)
	llvm-objcopy-cdm -O logisim $< $@

$(TARGET_BINARY): $(C_OBJECTS) $(LINKER_SCRIPT)
	$(LINK.c) $(LINKER_SCRIPT) $(filter %.o, $^) -o $@

$(C_OBJECTS): $(BUILD_DIR)/%.o: %
	@mkdir -p $(dir $@)
	$(COMPILE.c) $< -o $@ -MJ $@.command

$(COMPILE_COMMANDS): $(COMMANDS)
	rm -f $@
	echo "[" >> $@
	cat $^ | sed "s/,\?\s\+\"--target=cdm[a-z\-]*\"//g" >> $@
	echo "]" >> $@

$(COMMANDS): %.command: % ;

$(CDM_PLUGINS):
	curl --no-progress-meter -L $(CDM_PLUGIN_URL) | tar -xzOf - jar/$(notdir $@) > $@

$(TIME_PLUGIN):
	curl --no-progress-meter -L $(TIME_PLUGIN_URL) --create-dirs -o $@

.PHONY: dist
dist: all $(DIST_DIR) $(DIST_ZIP) $(DIST_TAR) 

$(DIST_ZIP): $(DIST_DIR)
	bsdtar -C $(dir $<) --format zip -cf $@ $(notdir $<)

$(DIST_TAR): $(DIST_DIR)
	tar -C $(dir $<) -czf $@ $(notdir $<)

$(DIST_DIR): $(DIST_ASSETS)
	mkdir -p $@
	cp $^ $@
	sed -i 's/"[^"]*\($(notdir $(TARGET_IMAGE))\)"/"\1"/g' $@/$(notdir $(LOGISIM_PROJECT))

.PHONY: clean
clean:
	rm -f $(COMPILE_COMMANDS)
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_BASE_DIR)
	rm -f $(LOGISIM_DIR)/*.jar

-include $(DEPS)
