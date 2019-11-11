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

#include "field.h"

Field::Field(std::string &&field) : field(std::forward<std::string>(field)) {

}

Field::Field(const std::string &field) : field(field) {

}

Field::Field(const Field &other) : field(std::move(other.field)) {

}

Field::Field(Field &&other) : field(std::move(other.field)) {

}

Field &Field::operator= (const Field &other) {
	field = other.field;

	return *this;
}

Field &Field::operator= (Field &&other) {
	field = std::move(other.field);

	return *this;
}

std::string &Field::getField() const {
	return const_cast<std::string &>(field);
}

b32 Field::stringStartsWith(const std::string &arg) {
	return ::stringStartsWith(arg, field);
}

b32 Field::stringStartsWith(std::string &&arg) {
	return stringStartsWith(arg);
}

b32 stringStartsWith(const std::string &arg, const std::string &field) {
    if (arg.size() < field.size())
        return False;

    for (std::size_t i = 0; i < field.size(); i++) {
        if (field[i] != arg[i])
            return False;
    }

    return True;
}

b32 Field::FieldComparer::operator() (const std::string &arg, const std::string &field) const {
	return ::stringStartsWith(arg, field);
}
