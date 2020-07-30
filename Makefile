#SRCS specifies which files to compile as part of the project
SRCS = src/*.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

C11FLAG = -std=c++11 -O -I include/
SDLLIB=-lSDL2 -lSDL2_image -lSDL2_ttf
Debug=-g -fno-inline

#This is the target that compiles our executable
all : $(SRCS)
	g++ $(C11FLAG) $(SRCS) -w $(SDLLIB) -o $(OBJ_NAME)

debug: $(SRCS)
	g++ $(C11FLAG) $(SRCS) -w $(Debug) $(SDLLIB) -o $(OBJ_NAME)

.PHONY : clean
clean:
	rm $(OBJ_NAME)