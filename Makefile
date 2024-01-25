# Makefile to compile the game

# Compiler
CC = gcc

# Compilation options
CFLAGS = -Wall -Wextra -std=c11

# Source and build directories
SRC_DIR = src
BUILD_DIR = build

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# List of object files generated from source files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
TARGET = Sokoban

# Libraries
LIBS = -lncurses -lSDL2 -lSDL2_image

# Default rule
all: $(BUILD_DIR) $(TARGET)

# Rule to create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to compile source files and generate the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Rule to compile each source file individually
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Do not delete intermediate files
.PRECIOUS: $(BUILD_DIR)/%.o

# Phony rule to indicate that 'clean' is not a real file
.PHONY: clean

