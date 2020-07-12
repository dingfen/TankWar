#OBJS specifies which files to compile as part of the project
OBJS = src/*.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

C11FLAG = -std=c++11 -I include/
SDLLIB=-lSDL2 -lSDL2_image -lSDL2_ttf

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(C11FLAG) $(OBJS) -w $(SDLLIB) -o $(OBJ_NAME)

debug: $(OBJS)
	g++ $(C11FLAG) $(OBJS) -w -g $(SDLLIB) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)