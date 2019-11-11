/*
* MIT License
*
* Copyright (c) 2017 hockeyhurd
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

#ifndef MAKEGEN_INTERPRETER_H
#define MAKEGEN_INTERPRETER_H

#include <vector>
#include <string>

#include "source.h"

#define INTERPRETER_INVALID_FLAG 0x80

using flag_t = u8;

typedef enum OptimizationLevel {
    OPT_INVALID = 0x80, OPT_DEBUG = 0, OPT_OFF = 1, OPT_LOW = 2, OPT_MED = 3, OPT_HIGH = 4
} OptLevel;

enum class OutputType {
    EMPTY = 0, EXE = 1, STATIC = 2, SHARED = 3
};

struct IFlags {
    OutputType outputType;
	std::string makefileName;
    std::string outputName;
    OptLevel optLevel;
    flag_t wall;
    flag_t wextra;
    flag_t werror;
	flag_t pedantic;
    flag_t stdver;
    flag_t cmode;
    std::vector<std::string> flags;

    explicit IFlags(const OutputType = OutputType::EMPTY, std::string && = "makefile", std::string && = "");

    b32 decode(const std::string &);
};

#if 0
void initIFlags(IFlags &);
void freeIFlags(IFlags &);
#endif

/**
*  Interprets command line arguments into gcc style compilation
*  that is used and passed to the internal maker to generate 
*  the makefile desired.
*
*  @param argc arg count.
*  @param argv arguments.
*  @param sourceFiles Pointer to an ArrayList of SourceFiles(s).
*  @param flags Pointer to IFlags struct to provided additional info to the maker.
*
*  @return Unsigned 32-bit int count of number of source files.  If any pointer is
*       NULL, the function will return 0.
*/
size_t interpretArgs(const u32, char **, std::vector<SourceFile> &, IFlags &);

#endif //MAKEGEN_INTERPRETER_H
