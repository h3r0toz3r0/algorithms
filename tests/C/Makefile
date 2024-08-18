# Compiler and flags
CC = gcc
CFLAGS = -I../C/include -Iinclude -I../../C/include  # Include headers from C/include and test/C/include
LDFLAGS = -lcunit

# Directories
SRC_DIR = ../C
TEST_SRC_DIR = src
OBJ_DIR = obj

# Source and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.c) $(wildcard $(TEST_SRC_DIR)/test_main.c)
TEST_OBJ = $(patsubst $(TEST_SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Executable names
TEST_EXEC = $(OBJ_DIR)/test_main

# Default target
all: $(OBJ) $(TEST_OBJ)
	@echo "All source files and test_main compiled."

# Compile all source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile all test source files
$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the test executable
$(TEST_EXEC): $(OBJ) $(TEST_OBJ)
	$(CC) $(OBJ) $(TEST_OBJ) -o $(TEST_EXEC) $(LDFLAGS)

# Execute compiled test suite
execute: $(TEST_EXEC)
	@echo "Executing test_main:"
	@./$(TEST_EXEC) $(EXTRA_ARGS)

# Clean object and executable files
clean:
	rm -rf $(OBJ_DIR)

# Allow extra arguments for the execute target
EXTRA_ARGS := $(if $(filter $(MAKECMDGOALS),execute),$(wordlist 2, $(words $(MAKECMDGOALS)),$(MAKECMDGOALS)))
