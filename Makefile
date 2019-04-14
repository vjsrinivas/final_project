C = g++
CFLAGS = -Wall
DEPS = game.h ltexture.h ltimer.h map.h
OBJ = game.o ltexture.o ltimer.o map.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
main: $(OBJ)
	g++ $(CFLAGS) -o $@ $^
