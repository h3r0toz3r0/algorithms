all:
	$(MAKE) -C C
	$(MAKE) -C C++

C:
	$(MAKE) -C C

C++:
	$(MAKE) -C C++

test:
	$(MAKE) -C tests/C

clean:
	$(MAKE) -C C clean
	$(MAKE) -C C++ clean

.PHONY: all clean C C++
