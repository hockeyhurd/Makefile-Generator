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

#include "source.h"

#ifndef MIN_FILE_LEN
#define MIN_FILE_LEN 4u
#endif

SourceFile::SourceFile(std::string fileName, const FileType fileType) : fileName(std::move(fileName)), fileType(fileType) {
}

b32 isValidSourceFile(SourceFile &file, b32 &cmode) {
    if (file.fileName.size() < MIN_FILE_LEN)
        return False;

    std::string subString;

    for (s64 i = (s64) file.fileName.size() - 1; i >= 0; i--) {
        if (file.fileName[i] == '.' && i + 1 < (s32) file.fileName.size()) {
            subString = &file.fileName[i + 1];
            break;
        }
    }

    if (subString.size() == 0)
        return False;

    if (subString == "h") {
        file.fileType = HEADER;
    }

    // else if (!stringCompare(subString, "hpp")) {
    else if (subString == "hpp") {
        file.fileType = HEADER;
        cmode = False;
    }

    else if (subString == "hxx") {
        file.fileType = HEADER;
        cmode = False;
    }

    else if (subString == "c")
        file.fileType = SOURCE;

    else if (subString == "cpp") {
        file.fileType = SOURCE;
        cmode = False;
    }

    else if (subString == "cxx") {
        file.fileType = SOURCE;
        cmode = False;
    }

    else
        return False;

    return True;
}
