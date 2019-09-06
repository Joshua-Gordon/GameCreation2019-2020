CC = clang++
FLAGS = -lSDL2 -lSDL2_image
EXEC = bones
SRC = src/*.cpp

all: $(SRC)
	$(CC) $(FLAGS) -o bin/$(EXEC) $(SRC)
