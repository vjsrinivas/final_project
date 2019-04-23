 C = g++
 CFLAGS = -Wall
 LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
 DEPS = Windows.cpp
 OBJ = Windows.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<
Windows: $(OBJ)
	g++ $(CFLAGS) $(LIBS) -o $@ $^
clean:
	rm Windows.o




