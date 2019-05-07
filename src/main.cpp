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

#include <vector>
#include <iostream>

#include "interpreter.h"
#include "maker.h"
// #include "filesystem.h"

#ifdef WIN32
#include <vld.h>
#endif

#define TEST 0

#if 0
static void printString(const String *);

void printString(const String *string) {
	printf("[%u]: %s\n", string->len, string->cstr);
}
#endif

s32 main(s32 argc, char **argv) {
	IFlags flags;

	std::vector<SourceFile> sourceFiles;

	if (!interpretArgs((const u32)argc, argv, sourceFiles, flags)) {
		std::cout << "Error collecting source flags...\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Collecting source files success!!\n";

	u32 fileNum = 0;

#if 0
	constructArrayListIterator(&iter, &sourceFiles);
	printf("Files:\n");
	while (hasNextArrayListIterator(&iter)) {
		SourceFile *sourceFile = (SourceFile *)nextArrayListIterator(&iter);
		printf("\t[%u]: %s\n", ++fileNum, sourceFile->fileName.cstr);
		// free(sourceFile->fileName.cstr);
	}
#elif 1
	for (auto &sourceFile : sourceFiles) {
		std::printf("\t[%u]: %s\n", ++fileNum, sourceFile.fileName.c_str());
}
#endif

	SRC source(flags.makefileName, sourceFiles);

	const b32 result = writeToFile(source, flags);

	if (!result) {
		std::cout << "ERROR: Writing \"" << flags.makefileName << "\"\n";
		exit(EXIT_FAILURE);
	}

	return 0;
}
