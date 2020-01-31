cmake_minimum_required(VERSION 3.16.2)
project(makegen)

#set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -O3 -Wall -Wextra -pedantic -Wfloat-equal -Wno-unused-parameter")

add_executable(makegen src/BuildOptions.cpp  src/FileReader.cpp  src/FileWriter.cpp  src/Flags.cpp  src/InputFile.cpp  src/MakeGen.cpp  src/Parser.cpp  src/SrcFile.cpp  src/StringCache.cpp  src/Target.cpp)
