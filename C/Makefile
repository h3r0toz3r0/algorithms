CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -I include
SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,obj/%.o,$(SOURCES))

obj/%.o: src/%.c 
	@mkdir -p obj
	$(CC) -c $(CFLAGS) $< -o $@

all: $(OBJECTS)

clean:
	rm -rf obj

.PHONY: all clean
