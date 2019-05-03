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

#include "interpreter.h"
#include "string.h"
#include "libs.h"
#include "link.h"
#include "name.h"
#include "optimization_level.h"
#include "stdver.h"
#include "warnings.h"

#include <algorithm>
#include <cstring>
#include <memory>
#include <vector>

#ifndef DEFAULT_C_STD
#define DEFAULT_C_STD 99u
#endif // !DEFAULT_C_STD

#define INTERPRETER_USE_BETA_DECODE 1

extern void myFree(void *, const char *);
extern void *myMalloc(const u32, const char *);

#if !INTERPRETER_USE_BETA_DECODE
static const char *flagVerCheck = "-std=c";
static const char *flagNameCheck = "-name=";
static const u32 flagNameCheckLen = 6;
static const u32 flagVerCheckLen = 6;
#endif

static void loadDefaultEnvironment(std::vector<SourceFile> &, IFlags &);

static void fillFieldVec(std::vector<Field *> &);
static Field *findField(const std::string &, std::vector<Field *> &);
static Field *binSearch(const std::string &, std::vector<Field *> &, const size_t, const size_t);

IFlags::IFlags(const OutputType outputType, std::string &&outputName) : outputType(outputType), outputName(outputName), optLevel(OPT_INVALID), wall(INTERPRETER_INVALID_FLAG),
	wextra(INTERPRETER_INVALID_FLAG), werror(INTERPRETER_INVALID_FLAG), pedantic(INTERPRETER_INVALID_FLAG) , stdver(INTERPRETER_INVALID_FLAG), cmode(INTERPRETER_INVALID_FLAG) {

	flags.reserve(0x10);
}

b32 IFlags::decode(const std::string &arg) {
#if !INTERPRETER_USE_BETA_DECODE
	static const std::string temp = "-l";

	if (arg == "-Wall")
		wall = 1;
	else if (arg == "-Wextra")
		wextra = 1;
	else if (arg == "-Werror")
		werror = 1;
	else if (arg == "-pedantic")
		pedantic = 1;
	else if (arg == "-pedantic-errors")
		pedantic = 2;
	else if (arg == "-g")
		optLevel = OptLevel::OPT_DEBUG;
	else if (arg == "-O0")
		optLevel = OptLevel::OPT_OFF;
	else if (arg == "-O1")
		optLevel = OptLevel::OPT_LOW;
	else if (arg == "-O2")
		optLevel = OptLevel::OPT_MED;
	else if (arg == "-O3")
		optLevel = OptLevel::OPT_HIGH;
	else if (arg == "-pipe") {
		flags.emplace_back("-pipe");
	}

	else if (arg == "-pthread") {
		flags.emplace_back("-pthread");
	}

	else if (arg == "-exe") {
		if (outputType == OutputType::EMPTY)
			outputType = OutputType::EXE;
		else
			return False;
	}

	else if (arg == "-static") {
		if (outputType == OutputType::EMPTY)
			outputType = OutputType::STATIC;
		else
			return False;
	}

	else if (arg == "-shared") {
		if (outputType == OutputType::EMPTY)
			outputType = OutputType::SHARED;
		else
			return False;
	}

	// Below needs to be verified as incorrect! (Temp deprecated!).
#if 0
	else if (!stringCompare(arg->cstr, "-gtest")) {
		String *gtest = (String *)myMalloc(sizeof(String), "Malloc -gtest flag");
		constructString(gtest, "-gtest");

		addArrayList(&flags->flags, gtest);
	}
#endif

	else if (arg[0] == temp[0] && arg[1] == temp[1]) {
		// String *link = (String *) myMalloc(sizeof(String), "Malloc -l flag");
		// constructString(link, arg->cstr);

		// addArrayList(&flags->flags, link);
		flags.emplace_back(arg);
	}

	// Could be "-name=<insert name here>"
	else if (arg.size() >= flagNameCheckLen) {
		for (u32 i = 0; i < flagNameCheckLen; i++) {
			if (arg[i] != flagNameCheck[i]) {
				goto CHECK;
				return False;
			}
		}

		// Valid name, set appropriate flags.
		// constructString(&flags->outputName, arg->cstr + 6);
		outputName = arg.c_str() + 6;
	}

	// -std=c11, -std=c++11
	// Check for stdver:
	else if (arg.size() == 8 || arg.size() == 10) {
	CHECK:;
		u32 i;
		for (i = 0; i < flagVerCheckLen; i++) {
			if (arg[i] != flagVerCheck[i])
				return False;
		}

		if (arg.size() == 10) {
			if (arg[i++] != '+' || arg[i++] != '+')
				return False;
		}

		// flags->stdver
		String temp;
		temp.cstr = (char *)&arg.c_str()[i];
		temp.len = stringLength(temp.cstr);

		u32 output = 0;

		parseUInt(&temp, &output);
		stdver = (flag_t)(output & 0xff);
	}

	else
		return False;

	return True;
#else
	static std::vector<Field *> fieldVec;

	if (fieldVec.empty()) {
		fillFieldVec(fieldVec);
	}

#if 0
	for (auto &fieldPtr : fieldVec) {
		if (fieldPtr->stringStartsWith(arg)) {
			fieldPtr->apply(arg, *this);
			break;
		}
	}
#else
	Field *field = findField(arg, fieldVec);

	if (field == nullptr)
		return False;

	field->apply(arg, *this);
#endif

	return True;
#endif
}

void fillFieldVec(std::vector<Field *> &fieldVec) {
	static FieldSharedLibs sharedLibs;
	static FieldStaticLibs staticLibs;
	static FieldExe exe;
	static FieldLink link;
	static FieldName name;
	static FieldDebugLevel debugLevel;
	static FieldOptimizationLevel optLevel;
	static FieldStdVer stdVer;
	static FieldWarnings warnings;

	fieldVec.emplace_back(&sharedLibs);
	fieldVec.emplace_back(&staticLibs);
	fieldVec.emplace_back(&exe);
	fieldVec.emplace_back(&name);
	fieldVec.emplace_back(&link);
	fieldVec.emplace_back(&debugLevel);
	fieldVec.emplace_back(&optLevel);
	fieldVec.emplace_back(&stdVer);
	fieldVec.emplace_back(&warnings);

	static auto sortFunc = [](Field *left, Field *right) {
		return left->getField() < right->getField();
	};

	std::sort(fieldVec.begin(), fieldVec.end(), sortFunc);
	// std::sort(fieldVec.begin(), fieldVec.end(), sortFunc2);
}

Field *findField(const std::string &arg, std::vector<Field *> &fieldVec) {
	const size_t low = 0;
	const size_t high = fieldVec.size();
	
	Field *result = binSearch(arg, fieldVec, low, high);

	return result;
}

Field *binSearch(const std::string &arg, std::vector<Field *> &fieldVec, const size_t low, const size_t high) {
	if (high >= low) {
		const size_t mid = low + (high - low) / 2;
		const auto &temp = fieldVec[mid];

		if (temp->stringStartsWith(arg)) {
			return temp;
		}

		else if (arg < temp->getField())
			return binSearch(arg, fieldVec, low, mid - 1);

		return binSearch(arg, fieldVec, mid + 1, high);
	}

	return nullptr;
}

void loadDefaultEnvironment(std::vector<SourceFile> &sourceFiles, IFlags &flags) {
	/*
	*   -pipe -pthread -gtest -g -Wall -std=c11 -name=makegen main.c arraylist.c
	*   interpreter.c maker.c source.c string.c types.c
	*/

	// SourceFile *mainFile = &fileBuf[bufIndex++];
	// SourceFile *exFile = &fileBuf[bufIndex++];

	// constructString(&mainFile->fileName, "main.c");
	// constructString(&exFile->fileName, "ex.c");

	// mainFile->fileType = SOURCE;
	// exFile->fileType = SOURCE;

	// addArrayList(sourceFiles, mainFile);
	// addArrayList(sourceFiles, exFile);
	sourceFiles.emplace_back("main.c", FileType::SOURCE);
	sourceFiles.emplace_back("ex.c", FileType::SOURCE);

	flags.optLevel = OPT_DEBUG;
	flags.wall = 1;
	flags.stdver = DEFAULT_C_STD;
	flags.cmode = True;
	// constructString(&flags->outputName, "main");
	flags.outputName = "main";

	// String *pipe = (String *) myMalloc(sizeof(String), "Malloc -pipe flag");
	// constructString(pipe, "-pipe");

	// addArrayList(&flags->flags, pipe);
	flags.flags.emplace_back("-pipe");
}

#if 0
void initIFlags(IFlags &flags) {
	flags.optLevel = OPT_INVALID;
	flags.wall = INTERPRETER_INVALID_FLAG;
	flags.stdver = INTERPRETER_INVALID_FLAG;
	flags.cmode = INTERPRETER_INVALID_FLAG;
	flags.outputName = "";

	flags.flags.reserve(0x10);
}

void freeIFlags(IFlags &flags) {
	flags.optLevel = OPT_INVALID;
	flags.wall = INTERPRETER_INVALID_FLAG;
	flags.stdver = INTERPRETER_INVALID_FLAG;
	flags.cmode = INTERPRETER_INVALID_FLAG;

	flags.flags.clear();
}
#endif

size_t interpretArgs(const u32 argc, char **argv, std::vector<SourceFile> &sourceFiles, IFlags &flags) {
	if (argc <= 1 || argv == nullptr)
		return 0;

	/*ArrayList *sourceFiles = (ArrayList *) malloc(sizeof(ArrayList));

	if (sourceFiles == NULL) {
		free(sourceFiles);
		perror("Error allocating space for an ArrayList!\n");
		exit(-1);
		return NULL;
	}*/

	// constructArrayList(sourceFiles, 0x10, sizeof(SourceFile));

	if (!strcmp(argv[1], "--example")) {
		loadDefaultEnvironment(sourceFiles, flags);
		return sourceFiles.size();
	}

	for (u32 i = 1; i < argc; i++) {
		std::string arg = argv[i];

		// Is argument.
		if (arg[0] == '-') {
			if (!flags.decode(arg)) {
				perror("Error parsing flag: ");
				perror(arg.c_str());
				perror("\n");
				// cleanupAllocs(sourceFiles);
				exit(-1);
			}
		}

		// Else check if a valid source file.
		else {
			// SourceFile *file = &fileBuf[bufIndex++];
			// file->fileName = arg;
			SourceFile file(arg);
			b32 cmode = True;

			if (isValidSourceFile(file, cmode)) {
				// If valid we need to deep copy file name.
				// copyString(&file->fileName, &arg);
				// constructString(&file->fileName, arg.cstr);

				// Add to source file list.
				// addArrayList(sourceFiles, file);
				sourceFiles.push_back(std::move(file));

				if (!cmode)
					flags.cmode = 0;
				else if (flags.cmode == INTERPRETER_INVALID_FLAG)
					flags.cmode = static_cast<flag_t>(cmode);
			}
		}
	}

	// Make sure the output type is known.
	if (flags.outputType == OutputType::EMPTY) {
		flags.outputType = OutputType::EXE;
	}

	return sourceFiles.size();
}
