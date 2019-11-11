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

/**
 * @author hockeyhurd
 * @version 2019-05-01
 */

#include "stdver.h"
#include "string.h"

FieldStdVer::FieldStdVer() : Field("-std=c") {

}

b32 FieldStdVer::apply(const std::string &arg, IFlags &flags) {
    if (arg.size() == 8 || arg.size() == 10) {
        static const std::string flagCheck = "-std=c";

        if (!::stringStartsWith(arg, field)) {
            return False;
        }

        u32 i = 6;

        if (arg.size() == 10) {
            if (arg[i++] != '+' || arg[i++] != '+')
                return False;
        }

        String temp;
        temp.cstr = (char *) &arg.c_str()[i];
        temp.len = stringLength(temp.cstr);

        u32 output = 0;

        parseUInt(&temp, &output);
        flags.stdver = (flag_t) (output & 0xFF);
    }

    return True;
}
