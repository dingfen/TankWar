#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

C11FLAG = -std=c++11

SDLLIB=-lSDL2 -lSDL2_image

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) $(C11FLAG) -w $(SDLLIB) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)