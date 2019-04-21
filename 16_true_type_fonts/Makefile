C = g++
CFLAGS = -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
DEPS = 16_true_type_fonts.cpp 
OBJ = 16_true_type_fonts.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<
main: $(OBJ)
	g++ $(CFLAGS) $(LIBS) -o $@ $^
clean:
	rm main.o game.o ltexture.o ltimer.o map.o
