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

#include "optimization_level.h"

FieldOptimizationLevel::FieldOptimizationLevel() : Field("-O") {

}

b32 FieldOptimizationLevel::apply(const std::string &arg, IFlags &flags) {
	if (arg == "-O0")
		flags.optLevel = OptLevel::OPT_OFF;
	else if (arg == "-O1")
		flags.optLevel = OptLevel::OPT_LOW;
	else if (arg == "-O2")
		flags.optLevel = OptLevel::OPT_MED;
	else if (arg == "-O3")
		flags.optLevel = OptLevel::OPT_HIGH;
	else
		return False;

	return True;
}

FieldDebugLevel::FieldDebugLevel() : Field("-g") {

}

b32 FieldDebugLevel::apply(const std::string &arg, IFlags &flags) {
	flags.optLevel = OptLevel::OPT_DEBUG;

	return True;
}