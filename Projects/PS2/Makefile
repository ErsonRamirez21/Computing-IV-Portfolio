CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++14
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
DEPS = CelestialBody.h Universe.h 

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

all: NBody

NBody: CelestialBody.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm *.o NBody
