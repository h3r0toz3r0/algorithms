# Compiler and flags
CC ?= gcc
CFLAGS = -I../../C/include -Iinclude # Include headers from C/include and include
LDFLAGS = -lcunit

# Directories
TEST_SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ACTUAL_OBJ_DIR = ../../C/obj

# Source and object files
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.c) test_main.c
TEST_OBJ = $(patsubst $(TEST_SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(wildcard $(TEST_SRC_DIR)/*.c)) $(OBJ_DIR)/test_main.o
ACTUAL_OBJ = $(shell find $(ACTUAL_OBJ_DIR) -type f -name "*.o")

# Executable names
TEST_EXEC = $(BIN_DIR)/test_main

.PHONY: all clean execute valgrind

# Default target
all: $(OBJ_DIR) $(BIN_DIR) $(TEST_EXEC)
	@echo "All source files and test_main compiled."

# Create directories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compile all test source files
$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test_main.c
$(OBJ_DIR)/test_main.o: test_main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c test_main.c -o $(OBJ_DIR)/test_main.o

# Link the test executable
$(TEST_EXEC): $(TEST_OBJ) $(ACTUAL_OBJ) | $(BIN_DIR)
	$(CC) $(TEST_OBJ) $(ACTUAL_OBJ) -o $(TEST_EXEC) $(LDFLAGS)

# Execute compiled test suite
execute: $(TEST_EXEC)
	@echo "Executing test_main with arguments: $(ARGS)"
	@./$(TEST_EXEC) $(ARGS)

# Run tests with Valgrind
valgrind: $(TEST_EXEC)
	@echo "Running tests with Valgrind:"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_EXEC) $(ARGS)

# Clean object and executable files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Capture additional arguments after `make execute`
ARGS = $(filter-out $@,$(MAKECMDGOALS))

# Prevent make from interpreting additional arguments as targets
%:
	@: