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

#include <iostream>

#include "interpreter.h"
#include "maker.h"

#ifdef WIN32
#include <vld.h>
#endif

static void pause() {
#if OS_WIN
	std::cout << "Press enter to continue.\n";
	std::cin.get();
#endif
}

#define TEST 0

s32 main(s32 argc, char **argv) {
#if TEST

#else
    IFlags flags;

	std::vector<SourceFile> sourceFiles;

    if (!interpretArgs(argc, argv, sourceFiles, flags)) {
        printf("Error collecting source flags...\n");
    }

    else {
        printf("Collecting source files success!!\n");

        u32 fileNum = 0;

		std::cout << "Files:\n";

		for (auto &sourceFile : sourceFiles) {
			printf("\t[%u]: %s\n", ++fileNum, sourceFile.fileName.c_str());
		}

		Source source("makefile", "", sourceFiles);

#if 0
        constructArrayListIterator(&iter, &sourceFiles);
        while (hasNextArrayListIterator(&iter)) {
            SourceFile *sourceFile = (SourceFile *) nextArrayListIterator(&iter);
            // printf("\t[%u]: %s\n", ++fileNum, sourceFile->fileName.cstr);
            // free(sourceFile->fileName.cstr);
            myFree(sourceFile->fileName.cstr, "SourceFile's String");
        }
#endif

    }

#endif
    pause();
    return 0;
}
