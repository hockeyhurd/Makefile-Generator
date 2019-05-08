CC = g++
CC_FLAGS = -pipe -O2 -Wall -pedantic -std=c++11
all: link main.o carraylist.o field.o filesystem.o interpreter.o libs.o link.o makefile_name.o maker.o name.o optimization_level.o source.o stdver.o string.o types.o warnings.o 

main.o: main.cpp
	$(CC) $(CC_FLAGS) -c main.cpp
carraylist.o: carraylist.cpp
	$(CC) $(CC_FLAGS) -c carraylist.cpp
field.o: field.cpp
	$(CC) $(CC_FLAGS) -c field.cpp
filesystem.o: filesystem.cpp
	$(CC) $(CC_FLAGS) -c filesystem.cpp
interpreter.o: interpreter.cpp
	$(CC) $(CC_FLAGS) -c interpreter.cpp
libs.o: libs.cpp
	$(CC) $(CC_FLAGS) -c libs.cpp
link.o: link.cpp
	$(CC) $(CC_FLAGS) -c link.cpp
makefile_name.o: makefile_name.cpp
	$(CC) $(CC_FLAGS) -c makefile_name.cpp
maker.o: maker.cpp
	$(CC) $(CC_FLAGS) -c maker.cpp
name.o: name.cpp
	$(CC) $(CC_FLAGS) -c name.cpp
optimization_level.o: optimization_level.cpp
	$(CC) $(CC_FLAGS) -c optimization_level.cpp
source.o: source.cpp
	$(CC) $(CC_FLAGS) -c source.cpp
stdver.o: stdver.cpp
	$(CC) $(CC_FLAGS) -c stdver.cpp
string.o: string.cpp
	$(CC) $(CC_FLAGS) -c string.cpp
types.o: types.cpp
	$(CC) $(CC_FLAGS) -c types.cpp
warnings.o: warnings.cpp
	$(CC) $(CC_FLAGS) -c warnings.cpp
link: main.o carraylist.o field.o filesystem.o interpreter.o libs.o link.o makefile_name.o maker.o name.o optimization_level.o source.o stdver.o string.o types.o warnings.o 
	$(CC) $(CC_FLAGS) -o makegen main.o carraylist.o field.o filesystem.o interpreter.o libs.o link.o makefile_name.o maker.o name.o optimization_level.o source.o stdver.o string.o types.o warnings.o 
clean:
	rm -f *.o makegen