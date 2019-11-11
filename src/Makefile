#CC=g++
CC=clang++
CC_FLAGS=-pipe -std=c++17 -g -O0 -Wall -Wextra -pedantic
LD_FLAGS=#-pipe
NAME="makegen"
RM=rm

all: link MakeGen.o BuildOptions.o Flags.o File.o SrcFile.o Target.o StringCache.o

MakeGen.o: MakeGen.cpp
	$(CC) $(CC_FLAGS) -c MakeGen.cpp

BuildOptions.o: BuildOptions.cpp
	$(CC) $(CC_FLAGS) -c BuildOptions.cpp
Flags.o: Flags.cpp
	$(CC) $(CC_FLAGS) -c Flags.cpp

File.o: File.cpp
	$(CC) $(CC_FLAGS) -c File.cpp

SrcFile.o: SrcFile.cpp
	$(CC) $(CC_FLAGS) -c SrcFile.cpp

Target.o: Target.cpp
	$(CC) $(CC_FLAGS) -c Target.cpp

StringCache.o: StringCache.cpp
	$(CC) $(CC_FLAGS) -c StringCache.cpp

link: MakeGen.o BuildOptions.o Flags.o File.o SrcFile.o Target.o StringCache.o
	$(CC) $(LD_FLAGS) -o $(NAME) MakeGen.o BuildOptions.o Flags.o File.o SrcFile.o Target.o StringCache.o

clean:
	$(RM) -f *.o $(NAME)
