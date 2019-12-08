CLANG=clang++
GCC=g++
DEBUG=Debug
RELEASE=Release

LD_FLAGS=-pipe
NAME="makegen"
RM=rm

ifdef CFG
	ifneq ($(CFG),$(DEBUG))
        CC_FLAGS=-pipe -std=c++17 -O2 -Wall -Wextra -pedantic -Wno-unused-parameter
	else
        CC_FLAGS=-pipe -std=c++17 -g -O0 -Wall -Wextra -pedantic -Wno-unused-parameter
	endif
else
    CC_FLAGS=-pipe -std=c++17 -O2 -Wall -Wextra -pedantic -Wno-unused-parameter
endif

ifndef CC
	CC=$(GCC)
endif

all: link MakeGen.o BuildOptions.o Flags.o FileWriter.o Parser.o SrcFile.o Target.o StringCache.o

MakeGen.o: MakeGen.cpp
	$(CC) $(CC_FLAGS) -c MakeGen.cpp

BuildOptions.o: BuildOptions.cpp
	$(CC) $(CC_FLAGS) -c BuildOptions.cpp
Flags.o: Flags.cpp
	$(CC) $(CC_FLAGS) -c Flags.cpp

FileWriter.o: FileWriter.cpp
	$(CC) $(CC_FLAGS) -c FileWriter.cpp

Parser.o: Parser.cpp
	$(CC) $(CC_FLAGS) -c Parser.cpp

SrcFile.o: SrcFile.cpp
	$(CC) $(CC_FLAGS) -c SrcFile.cpp

Target.o: Target.cpp
	$(CC) $(CC_FLAGS) -c Target.cpp

StringCache.o: StringCache.cpp
	$(CC) $(CC_FLAGS) -c StringCache.cpp

link: MakeGen.o BuildOptions.o Flags.o FileWriter.o Parser.o SrcFile.o Target.o StringCache.o
	$(CC) $(LD_FLAGS) -o $(NAME) MakeGen.o BuildOptions.o Flags.o FileWriter.o Parser.o SrcFile.o Target.o StringCache.o

clean:
	$(RM) -f *.o $(NAME)
