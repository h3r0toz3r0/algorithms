# Compiler and flags
CC ?= gcc
CFLAGS = -I../../C/include -Iinclude # Include headers from C/include and test/C/include
LDFLAGS = -lcunit

# Directories
SRC_DIR = ../C
TEST_SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.c) $(wildcard $(TEST_SRC_DIR)/test_main.c)
TEST_OBJ = $(patsubst $(TEST_SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Executable names
TEST_EXEC = $(BIN_DIR)/test_main

# Default target
all: $(OBJ) $(TEST_OBJ)
	@echo "All source files and test_main compiled."

# Compile all source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile all test source files
$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the test executable
$(TEST_EXEC): $(OBJ) $(TEST_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) $(TEST_OBJ) -o $(TEST_EXEC) $(LDFLAGS)

# Execute compiled test suite
execute: $(TEST_EXEC)
	@echo "Executing test_main with arguments: $(ARGS)"
	@./$(TEST_EXEC) $(ARGS)

# Run tests with Valgrind
valgrind: $(TEST_EXEC)
	@echo "Running tests with Valgrind:"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_EXEC) $(ARGS)

# Code formatting with clang-format
format:
	@echo "Formatting code with clang-format..."
	@clang-format-15 -i $(SRC) $(TEST_SRC) || true

# Clean object and executable files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Capture additional arguments after `make execute`
ARGS = $(filter-out $@,$(MAKECMDGOALS))

# Prevent make from interpreting additional arguments as targets
%:
	@:
