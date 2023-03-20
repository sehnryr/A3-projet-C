# Variables
CC = gcc

# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -Werror: Treat warnings as errors
# -pedantic: Enable pedantic warnings
# -std=c99: Use C99 standard
# -O3: Optimize for speed
# -Og: Optimize for debugging
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c17 -O3 -Og

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BUILD_DIR = build

TARGET = $(BUILD_DIR)/main

# Get all .c files in src and subdirectories
SRC_FILES = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c)
# Replace .c with .o
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ -lstdc++fs -I$(INCLUDE_DIR)

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
