CC = gcc
CC_VER = -std=c99
CC_FLAGS = $(CC_VER) -g -Wall 

all: example.o main

example.o: example.c
	$(CC) $(CC_FLAGS) -c example.c

main: main.c
	$(CC) -o main $(CC_FLAGS) main.c example.o 

clean:
	rm *.o main