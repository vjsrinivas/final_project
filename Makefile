C = g++
CFLAGS = -Wall
LIBS = -lSDL2 -lSDL2_image
DEPS = main.cpp game.h ltexture.h ltimer.h map.h
OBJ = main.o game.o ltexture.o ltimer.o map.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<
main: $(OBJ)
	g++ $(CFLAGS) $(LIBS) -o $@ $^
clean:
	rm main.o game.o ltexture.o ltimer.o map.o
