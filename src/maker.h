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

#ifndef MAKEGEN_MAKER_H
#define MAKEGEN_MAKER_H

#include "source.h"
#include "interpreter.h"

#define CC_VAR "$(CC)"
#define CC_FLAGS_VAR "$(CC_FLAGS)"
#define CPP_VAR "$(CPP)"
#define MAKEFILE_VAR "makefile"
#define DEFAULT_FLAGS "$(CC_VER) -g -Wall"
#define DEFAULT_C_STD 99u
#define DEFAULT_CPP_STD 98u

class Source {

private:

	std::string fileName;
	std::string flags;
	std::vector<SourceFile> sourceFiles;

public:

	Source(std::string, std::string, std::vector<SourceFile> = std::vector<SourceFile>());
	Source(const Source &);
	Source(Source &&);
	~Source() = default;

	Source &operator= (const Source &);
	Source &operator= (Source &&);

	void add(const SourceFile &);
	b32 writeToFile(const IFlags &);

private:

	void writeMakefileHeaderVars(IFlags &, const FILE *);
	b32 writeMakefileOptimizationLevel(const OptLevel, const b32, const FILE *);
	void writeMakefileModules(IFlags &, const FILE *);

	static void writeString(const std::string &, const FILE *);
	static void writeChar(const char, const FILE *);
	static void writeCString(const char *, const FILE *);
	static void writeActualFileName(const SourceFile &, const FILE *);

	static b32 isValidSTDVersion(const b32, const u32);

};

#if USE_C_SRC
void constructSources(SRC *, std::string, std::vector<SourceFile> *);
void destructSources(SRC *);
void addSourceFile(const SRC *, const SourceFile &);

b32 writeToFile(const SRC *, const IFlags *);
#endif

#endif //MAKEGEN_MAKER_H
