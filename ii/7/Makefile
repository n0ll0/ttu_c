# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -g
LDFLAGS := 

# Directories
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Main target
TARGET := $(BIN_DIR)/program

# Phony targets
.PHONY: all clean


# Default target
all: $(TARGET) run

# Linking
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run:
	./$(TARGET)

# Include dependencies
-include $(OBJS:.o=.d)

# Generate dependencies
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

# Debug target
debug: CFLAGS += -DDEBUG
debug: all

# Release target
release: CFLAGS += -O2 -DNDEBUG
release: all