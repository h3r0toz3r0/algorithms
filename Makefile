all:
	$(MAKE) -C C
	$(MAKE) -C C++

C:
	$(MAKE) -C C

C++:
	$(MAKE) -C C++

test:
	$(MAKE) -tests/C/test

clean:
	$(MAKE) -C C clean
	$(MAKE) -C C++ clean

.PHONY: all clean C C++
