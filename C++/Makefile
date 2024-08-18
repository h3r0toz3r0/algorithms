CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -Wpedantic -I include
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

obj/%.o: src/%.cpp 
	@mkdir -p obj
	$(CXX) -c $(CXXFLAGS) $< -o $@

all: $(OBJECTS)

clean:
	rm -rf obj

.PHONY: all clean
