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

#include "warnings.h"

FieldWarnings::FieldWarnings() : Field("-W") {

}

b32 FieldWarnings::apply(const std::string &arg, IFlags &flags) {
	if (arg == "-Wall")
		flags.wall = 1;
	else if (arg == "-Wextra")
		flags.wextra = 1;
	else if (arg == "-Werror")
		flags.werror = 1;
	else
		return False;

	return True;
}

FieldPedantic::FieldPedantic() : Field("-pedantic") {

}

b32 FieldPedantic::apply(const std::string &args, IFlags &flags) {
	if (args == "-pedantic")
		flags.pedantic = 1;
	else if (args == "-pedantic-errors")
		flags.pedantic = 2;
	else
		return False;

	return True;
}
