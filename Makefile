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

.PHONY: all clean C C++ test

# Capture additional arguments after `make execute`
ARGS = $(filter-out $@,$(MAKECMDGOALS))

# Prevent make from interpreting additional arguments as targets
%:
	@: