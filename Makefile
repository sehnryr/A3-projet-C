# Variables
CC = gcc

# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -pedantic: Enable pedantic warnings
# -std=c17: Use C17 standard
# -O3: Optimize for speed
# -Og: Optimize for debugging
CFLAGS = -Wall -Wextra -pedantic -std=c17 -O3 -Og

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

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

.PHONY: clean autotests simulation
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

autotests: $(TARGET) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $^ test/test_autotests.c -lstdc++fs -I$(INCLUDE_DIR)

simulation: $(TARGET) $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $^ test/test_sim.c -lstdc++fs -I$(INCLUDE_DIR)
