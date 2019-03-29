#OBJS specifies which files to compile as part of the project
OBJS = 26_motion.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = 26_motion

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
