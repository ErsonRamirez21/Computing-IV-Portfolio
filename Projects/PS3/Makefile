# Compiler and flags
CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++14

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Header files
DEPS = Triangle.h

# Build object files
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

# Build all targets
all: TFractal

# Build the final executable
TFractal: Triangle.o TFractal.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Clean up build files
clean:
	rm *.o TFractal
