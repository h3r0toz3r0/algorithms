# Default targets
all: C C++

C:
	$(MAKE) -C C

C++:
	$(MAKE) -C C++

# Forward arguments to the tests/C/Makefile
test: C
	$(MAKE) -C tests/C $(ARGS)

clean:
	$(MAKE) -C C clean
	$(MAKE) -C C++ clean
	$(MAKE) -C tests/C clean

# Code formatting with clang-format
TEST_SRC = $(wildcard tests/C/src/*.c) tests/C/test_main.c
ACTUAL_SRC = $(wildcard C/src/*.c)

format:
	@echo "Formatting code with clang-format..."
	@clang-format-15 -i $(TEST_SRC) || true
	@clang-format-15 -i $(ACTUAL_SRC) || true

.PHONY: all clean C C++ test format

# Capture additional arguments after `make execute`
ARGS = $(filter-out $@,$(MAKECMDGOALS))

# Prevent make from interpreting additional arguments as targets
%:
	@: