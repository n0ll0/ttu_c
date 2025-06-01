# Compiler
CC = gcc 

# Compiler flags
CFLAGS = -Iinclude -Ilibs -Wall -Wextra -I"C:\Program Files\sqlite3" -L"C:\Program Files\sqlite3"

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

# Detect OS
ifeq ($(OS),Windows_NT)
	MKDIR_P = if not exist "$(1)" mkdir "$(1)"
	RM_RF = rmdir /s /q "$(1)"
	DEL = del /q "$(1)"
	EXE_EXT =
	RUN = $(TARGET)
else
	MKDIR_P = mkdir -p "$(1)"
	RM_RF = rm -rf "$(1)"
	DEL = rm -f "$(1)"
	EXE_EXT =
	RUN = ./$(TARGET)
endif

# Default target
all: $(TARGET)


# Link
$(TARGET): $(OBJ_FILES)
	@$(call MKDIR_P,$(BIN_DIR))
	$(CC) $(OBJ_FILES) -o $@ -Llibs -lsqlite3

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call MKDIR_P,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	-$(call RM_RF,$(OBJ_DIR))
	-$(call RM_RF,$(BIN_DIR))

run: all
	$(RUN)

# Phony targets
.PHONY: all clean run
