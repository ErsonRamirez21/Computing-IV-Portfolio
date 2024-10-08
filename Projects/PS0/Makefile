CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++14
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

all: main

main: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm *.o main

lint:
	cpplint main.cpp
