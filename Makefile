CC = clang++
FLAGS = -g -lSDL2 -lSDL2_image -lSDL2_ttf
EXEC = bones
SRC = src/*.cpp src/util/*.cpp src/entities/*.cpp

all: $(SRC)
	$(CC) $(FLAGS) -o bin/$(EXEC) $(SRC)
