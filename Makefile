# Makefile for the project

# Define the compiler
CC = gcc

# Compiler flags
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -pedantic: Enable pedantic warnings
# -std=c17: Use C17 standard
# -O3: Optimize for speed
# -Og: Optimize for debugging
CFLAGS = -Wall -Wextra -pedantic -std=c17 -O3 -Og

# Define the directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BUILD_DIR = build
FTD2XX = libraries/ftd2xx

ifeq ($(OS),Windows_NT)
	FTD2XX_LIB = $(FTD2XX)/ftd2xx.lib
else
	FTD2XX_LIB = $(FTD2XX)/libftd2xx.a
endif

# Get all .c files in src and its subdirectories
SRC_FILES = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c)
# Replace .c with .o
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Create the build directory when a prequisite calls for it
$(BUILD_DIR)/%:
	@mkdir -p $(BUILD_DIR)

# Compile .c files to .o files when a prerequisite calls for it
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR) -I$(FTD2XX)

# Default goal
# This will be called when make is called without arguments
.DEFAULT_GOAL := simulation

# Function to initialize data.txt and consigne.txt
init := @touch data.txt consigne.txt && \
		echo "false" > data.txt && \
		echo "20.0" >> data.txt && \
		echo "10.0" >> data.txt && \
		echo "0.0" > consigne.txt

# Phony targets
# This will prevent make from trying to build a file named after the argument
# of the .PHONY directive
.PHONY: clean autotests simulation zip

# Clean the build directory
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

# Build the autotests executable
autotests: $(BUILD_DIR)/test_autotests $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $^ test/test_autotests.c -lstdc++fs -I$(INCLUDE_DIR)

# Build the simulation executable and initialize data.txt and consigne.txt
simulation: $(BUILD_DIR)/test_sim $(OBJ_FILES)
	$(init)
	$(CC) $(CFLAGS) -o $^ test/test_sim.c -lstdc++fs -I$(INCLUDE_DIR)

# Build the usb executable with the ftd2xx library and initialize data.txt 
# and consigne.txt
usb: $(BUILD_DIR)/test_usb $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $^ test/test_usb.c \
		-lstdc++fs \
		-I$(INCLUDE_DIR) \
		-I$(FTD2XX) $(FTD2XX_LIB)

# Build the zip file for the submission of the project
zip:
	@zip -r sources_AA_YM.zip \
	include \
	libraries \
	src \
	test \
	Makefile \
	README.md
