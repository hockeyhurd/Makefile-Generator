CC = gcc
CC_FLAGS = -g -std=c0
all: link main.o example.o 

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c
example.o: example.c
	$(CC) $(CC_FLAGS) -c example.c
link: main.o example.o 
	$(CC) $(CC_FLAGS) -o test main.o example.o 
clean:
	rm -f *.o test