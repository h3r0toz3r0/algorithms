# Default targets
all: C C++

C:
	$(MAKE) -C C

C++:
	$(MAKE) -C C++

# Forward arguments to the tests/C/Makefile
test:
	$(MAKE) -C tests/C ARGS="$(ARGS)"

clean:
	$(MAKE) -C C clean
	$(MAKE) -C C++ clean
	$(MAKE) -C tests/C clean

.PHONY: all clean C C++ test
