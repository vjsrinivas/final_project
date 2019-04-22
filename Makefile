 C = g++
 CFLAGS = -Wall
 LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
 DEPS = Viewports.cpp
 OBJ = Viewports.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<
main: $(OBJ)
	g++ $(CFLAGS) $(LIBS) -o $@ $^
clean:
	rm Viewports.o




