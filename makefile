CC = g++
CC_FLAGS = -pipe -g -Wall -std=c++11
all: link main.o interpreter.o maker.o string.o types.o filesystem.o source.o 

main.o: main.cpp
	$(CC) $(CC_FLAGS) -c main.cpp
interpreter.o: interpreter.cpp
	$(CC) $(CC_FLAGS) -c interpreter.cpp
maker.o: maker.cpp
	$(CC) $(CC_FLAGS) -c maker.cpp
string.o: string.cpp
	$(CC) $(CC_FLAGS) -c string.cpp
types.o: types.cpp
	$(CC) $(CC_FLAGS) -c types.cpp
filesystem.o: filesystem.cpp
	$(CC) $(CC_FLAGS) -c filesystem.cpp
source.o: source.cpp
	$(CC) $(CC_FLAGS) -c source.cpp
link: main.o interpreter.o maker.o string.o types.o filesystem.o source.o 
	$(CC) $(CC_FLAGS) -o makegen main.o interpreter.o maker.o string.o types.o filesystem.o source.o 
clean:
	rm -f *.o makegen