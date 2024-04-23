# Edited from the file from https://makefiletutorial.com/
TARGET_EXEC := tc
CC = gcc
BUILD_DIR := ./build
SRC_DIRS := ./src
LIB_DIRS := ./lib
BIN_DIR := ./bin
.DEFAULT_GOAL := generate

#if you wanna feel like a genius just get rid of debug symbol ;)
DEBUG =       

CFLAGS := -g -Wall


# random additional args (mainly going to be used for fsanitize
#ADDARGS := -fsanitize=address

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

SRCS += $(shell find $(LIB_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')


# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)

# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(DEBUG)$(CXX) $(OBJS) $(ADDARGS) -o $@ $(LDFLAGS)
	$(DEBUG)mv ./build/tc ./bin/tc

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	$(DEBUG)mkdir -p $(dir $@)
	$(DEBUG)$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: clean test test2 

clean:
	$(DEBUG)rm -rf $(BUILD_DIR)/*
	$(DEBUG)rm -rf $(BIN_DIR)/*
	$(DEBUG)rm -f ./*.class
	$(DEBUG)rm -f ./tests/codeGenerationTests/*.j
	$(DEBUG)echo "Cleaning Has Completed"

generate: $(BUILD_DIR)/$(TARGET_EXEC) 
	$(DEBUG)echo "Generation Has Completed"

test: 
	$(DEBUG)gdb --args $(BIN_DIR)/tc $(ARGS)

run: 
	$(DEBUG)./$(BIN_DIR)/tc $(ARGS)

#args in this case is the file that you would like to thow into the assembler
generateJasmin: 
	$(DEBUG)java -jar ./doc/CodeGen/jasmin-2.4/jasmin.jar $(ARGS)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
