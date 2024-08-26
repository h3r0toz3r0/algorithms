CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -Iinclude

# Find all C source files under src/ recursively
SOURCES = $(shell find src/ -type f -name "*.c")
# Create object files in obj/ with a corresponding directory structure
OBJECTS = $(patsubst src/%,obj/%,$(SOURCES:.c=.o))

# Ensure obj/ and its subdirectories are created
obj/%.o: src/%.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJECTS)

clean:
	rm -rf obj

.PHONY: all clean
