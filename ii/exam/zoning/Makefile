# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra -std=c99

DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# Directories
SRC_DIR = src
LIBS_DIR = libs
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) \
            $(wildcard $(SRC_DIR)/**/*.c)


# Object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable
TARGET = $(BIN_DIR)/my_program

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean
