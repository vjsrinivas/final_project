C = g++
CFLAGS = -Wall -std=c++11
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
DEPS = ltexture.h ltimer.h map.h game.h enemy.h player.h main.cpp
OBJ =  ltexture.o ltimer.o map.o game.o enemy.cpp player.o main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(LIBS) -c -g -o $@ $<
main: $(OBJ)
	g++ $(CFLAGS) $(LIBS) -o $@ $^
clean:
	rm player.o main.o game.o ltexture.o ltimer.o map.o
