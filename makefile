################################
##        Program config
################################
PROJECT_NAME    = serial_tool
BUILD_DIR 		= build
SOURCE_DIR 		= src
INC_DIR 		= inc
OUT_DIR 		= out

################################
##        Source config
################################
SOURCE          = 
SOURCE          += main.c
SOURCE          += lib.c

################################
##        Flags config
################################
CFLAGS          =
CFLAGS          += -std=c99
CFLAGS          += -Wall -Wpedantic -Werror

################################
##        Print config
################################
LDPRINT         = "Link   $@"
CCPRINT         = "Build  $<"

################################
##        Auto config
################################
OBJECTS         = $(addprefix $(BUILD_DIR)/, $(SOURCE:.c=.o))
CFLAGS          += -I $(INC_DIR)
PROJECT			= $(OUT_DIR)/$(PROJECT_NAME)

################################
##        Make config
################################
.DEFAULT_GOAL := all

################################
##           Targets
################################
all: clean build

build: $(PROJECT)

$(PROJECT): $(OBJECTS)
	@mkdir -p $(dir $@)
	@echo $(LDPRINT)
	@$(CC) -o $@ $(OBJECTS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo $(CCPRINT)
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(OUT_DIR)

run:
	@$(PROJECT)
