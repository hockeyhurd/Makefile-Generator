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

#include "maker.h"

#include <cstdio>

Source::Source(std::string fileName, std::string flags, std::vector<SourceFile> sourceFiles) : fileName(std::move(fileName)), flags(std::move(flags)), sourceFiles(std::move(sourceFiles)) {
	if (this->sourceFiles.capacity() < 0x10)
		this->sourceFiles.reserve(0x10);
}

Source::Source(const Source &source) : fileName(source.fileName), flags(source.flags), sourceFiles(source.sourceFiles) {

}

Source::Source(Source &&other) : fileName(std::move(other.fileName)), flags(std::move(other.flags)), sourceFiles(std::move(other.sourceFiles)) {

}

Source &Source::operator= (const Source &other) {
	fileName = other.fileName;
	flags = other.flags;
	sourceFiles = other.sourceFiles;

	return *this;
}

Source &Source::operator= (Source &&other) {
	fileName = std::move(other.fileName);
	flags = std::move(other.flags);
	sourceFiles = std::move(other.sourceFiles);

	return *this;
}

void Source::add(const SourceFile &file) {
	sourceFiles.push_back(file);
}

b32 Source::writeToFile(const IFlags &flags) {
	if (flags.cmode == INTERPRETER_INVALID_FLAG) {
		perror("Could not determine \"C-Mode\"!  Assuming mode 'C++'\n");
		const_cast<IFlags &>(flags).cmode = False;
	}

	FILE *outputFile = std::fopen(fileName.c_str(), "w");

	if (outputFile == NULL) {
		fclose(outputFile);
		perror("Error writing file: ");
		perror(fileName.c_str());
		perror("\n");
		return False;
	}

	IFlags &castFlags = const_cast<IFlags &>(flags);

	writeMakefileHeaderVars(castFlags, outputFile);
	writeChar('\n', outputFile);
	writeMakefileModules(castFlags, outputFile);

	fclose(outputFile);

	return True;
}

void Source::writeString(const std::string &word, const FILE *file) {
	for (auto ch : word)
        putc(ch, (FILE *) file);
}

void Source::writeCString(const char *word, const FILE *file) {
    for (char *c = (char *) word; *c != '\0'; c++)
        putc(*c, (FILE *) file);
}

void Source::writeChar(const char c, const FILE *file) {
    putc((char) c, (FILE *) file);
}

void Source::writeActualFileName(const SourceFile &file, const FILE *makefile) {
	for (auto c : file.fileName) {
		if (c == '.')
			break;

        writeChar(c, makefile);
    }
}

void Source::writeMakefileHeaderVars(IFlags &flags, const FILE *makefile) {
	this->flags = "";

    if (flags.cmode == True)
        writeCString("CC = gcc\n", makefile);
    else
        writeCString("CC = g++\n", makefile);

    writeCString("CC_FLAGS = ", makefile);

    b32 needsSpace = False;
    
    if (flags.flags.size()) {
        for (u32 i = 0; i < flags.flags.size(); i++) {
			const std::string &str = flags.flags.at(i);
            writeCString(str.c_str(), makefile);
            writeChar(' ', makefile);
        }
    }

    needsSpace = writeMakefileOptimizationLevel(flags.optLevel, needsSpace, makefile);

    if (flags.wall != INTERPRETER_INVALID_FLAG) {
        if (needsSpace) {
            writeCString(" -Wall", makefile);
			this->flags += " -Wall";
        }

        else {
            needsSpace = True;
            writeCString("-Wall", makefile);
			this->flags += "-Wall";
        }
    }

    if (flags.stdver != INTERPRETER_INVALID_FLAG) {
        std::string stdver = std::to_string(flags.stdver);
		
		{

            if (!isValidSTDVersion(flags.cmode, flags.stdver)) {
                perror("Invalid stdver! Please check your input!\n");
                
                if (flags.cmode)
                    flags.stdver = DEFAULT_C_STD;
                else
                    flags.stdver = DEFAULT_CPP_STD;

				std::to_string(flags.stdver);
            }

            if (needsSpace) {
                writeCString(" -std=", makefile);
				this->flags += " -std=";
            }

            else {
                needsSpace = True;
                writeCString("-std=", makefile);
				this->flags += "-std=";
            }

            if (flags.cmode) {
                writeCString("c", makefile);
				this->flags += "c";
            }

            else {
                writeCString("c++", makefile);
				this->flags += "c++";
            }

            writeString(stdver, makefile);
			this->flags += stdver;
        }
    }
}

b32 Source::writeMakefileOptimizationLevel(const OptLevel level, const b32 needsSpace, const FILE *makefile) {
    if (needsSpace)
        writeChar(' ', makefile);
    
    switch (level) {
    case OPT_DEBUG:
        writeCString("-g", makefile);
		this->flags += "-g";
        break;

    case OPT_OFF:
        writeCString("-O0", makefile);
		this->flags += "-O0";
        break;

    case OPT_LOW:
        writeCString("-O1", makefile);
		this->flags += "-O1";
        break;

    case OPT_MED:
        writeCString("-O2", makefile);
		this->flags += "-O2";
        break;

    case OPT_HIGH:
        writeCString("-O3", makefile);
		this->flags += "-O3";
        break;

    default:
        return False;
    }

    return True;
}

void Source::writeMakefileModules(IFlags &flags, const FILE *makefile) {
    writeCString("all: link ", makefile);

	for (auto &file : sourceFiles) {
		if (file.fileType == SOURCE) {
			writeActualFileName(file, makefile);
			writeCString(".o ", makefile);
		}
	}

    writeChar('\n', makefile);
    writeChar('\n', makefile);

	for (auto &file : sourceFiles) {
		if (file.fileType == SOURCE) {
			writeActualFileName(file, makefile);
			writeCString(".o: ", makefile);
			writeString(file.fileName, makefile);
			writeChar('\n', makefile);

			writeChar('\t', makefile);
			writeCString(CC_VAR, makefile);
			writeChar(' ', makefile);
			// writeString(&source->flags, makefile);
			writeCString(CC_FLAGS_VAR, makefile);
			writeCString(" -c ", makefile);
			writeString(file.fileName, makefile);
			writeChar('\n', makefile);
		}
	}

    writeCString("link: ", makefile);

	for (auto &file : sourceFiles) {
		if (file.fileType == SOURCE) {
			writeActualFileName(file, makefile);
			writeCString(".o ", makefile);
		}
	}

    writeCString("\n\t", makefile);
    writeCString(CC_VAR, makefile);
    writeChar(' ', makefile);
    writeCString(CC_FLAGS_VAR, makefile);
    writeChar(' ', makefile);

    if (flags.outputName.size()) {
        writeCString("-o ", makefile);
        writeString(flags.outputName, makefile);
        writeChar(' ', makefile);
    }

	for (auto &srcFile : sourceFiles) {
		if (srcFile.fileType == SOURCE) {
			writeActualFileName(srcFile, makefile);
			writeCString(".o ", makefile);
		}
	}

    writeCString("\nclean:\n\trm -f *.o", makefile);

    if (flags.outputName.size() > 0) {
        writeChar(' ', makefile);
        writeString(flags.outputName, makefile);
    }
}

b32 Source::isValidSTDVersion(const b32 cmode, const u32 version) {
    if (cmode == 1) {
        switch (version) {
        case 90:
            return True;
        case 99:
            return True;
        case 11:
            return True;
        // case 17: // Waiting C17/C18 standard...
            // break;
        default:
            return False;
        }
    }

    else {
        switch (version) {
        case 98:
            return True;
        case 11:
            return True;
        case 14:
            return True;
        case 17:
            return True;
		// case 20: // Waiting for C++20 standard
			// return True;
        default:
            return False;
        }
    }

    return False;
}