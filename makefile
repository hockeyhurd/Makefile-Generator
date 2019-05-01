CC = g++
CC_FLAGS = -g -Wall -std=c++11
all: link carraylist.o filesystem.o interpreter.o main.o maker.o source.o string.o types.o 

carraylist.o: carraylist.cpp
	$(CC) $(CC_FLAGS) -c carraylist.cpp
filesystem.o: filesystem.cpp
	$(CC) $(CC_FLAGS) -c filesystem.cpp
interpreter.o: interpreter.cpp
	$(CC) $(CC_FLAGS) -c interpreter.cpp
main.o: main.cpp
	$(CC) $(CC_FLAGS) -c main.cpp
maker.o: maker.cpp
	$(CC) $(CC_FLAGS) -c maker.cpp
source.o: source.cpp
	$(CC) $(CC_FLAGS) -c source.cpp
string.o: string.cpp
	$(CC) $(CC_FLAGS) -c string.cpp
types.o: types.cpp
	$(CC) $(CC_FLAGS) -c types.cpp
link: carraylist.o filesystem.o interpreter.o main.o maker.o source.o string.o types.o 
	$(CC) $(CC_FLAGS) -o makegen carraylist.o filesystem.o interpreter.o main.o maker.o source.o string.o types.o 
clean:
	rm -f *.o makegen