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

#include "string.h"

#include <iostream>

extern void myFree(void *, const char *);

#ifdef __cplusplus
extern "C" {
#endif

b32 isNum(const char c) {
    return (b32) (c >= '0' && c <= '9');
}

u32 charToNum(const char c) {
    return (b32) (c - '0');
}

// static const u32 p = 16777619u;
#define P_CONST 16777619u
u32 hashString(const char *str) {
    u32 hash = 2166136261u;

    while (*str != '\0') {
        hash = (hash ^ *str) * P_CONST;
        str++;
    }

    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;

    return hash;
}

u32 stringLength(const char *cstr) {
    if (cstr == NULL)
        return 0;

    u32 count = 0;

    while (cstr[count++] != '\0');

    return count;
}

s32 stringCompare(const char *left, const char *right) {
    if (left == NULL && right == NULL)
        return 0;
    else if (left != NULL && right == NULL)
        return 1;
    else if (left == NULL && right != NULL)
        return -1;

    u32 i;

    for (i = 0; left[i] != '\0'; i++) {
        if (right[i] == '\0' || left[i] > right[i])
            return 1;

        else if (left[i] < right[i])
            return -1;
    }

    return right[i] == '\0' ? 0 : 1;
}

b32 stringStartsWith(const String *string, const String *ref) {
    if ((string == NULL || ref == NULL || string->len < ref->len) && ref->len > 1)
        return False;

    for (u32 i = 0; i < ref->len - 1; i++) {
        if (string->cstr[i] != ref->cstr[i])
            return False;
    }

    return True;
}

b32 containsString(const String *string, const String *find) {
    if (string == NULL || find == NULL || string->len < find->len)
        return False;

    u32 index = 0;
    for (u32 i = 0; i < string->len; i++) {
        if (string->cstr[i] == find->cstr[index]) {
            if (++index == find->len - 1)
                return True;
        }

        else
            index = 0;
    }

    return index == find->len - 1;
}

b32 parseUInt(const String *string, u32 *output) {
    if (string == NULL || string->cstr == NULL || !string->len || output == NULL)
        return False;

	u32 buffer = 0;

    u32 power = 1;
    for (s32 i = string->len - 2; i >= 0; i--) {
        if (!isNum(string->cstr[i]))
            return False;

        buffer += charToNum(string->cstr[i]) * power;
        power *= 10;
    }

	*output = buffer;

    return True;
}

b32 parseInt(const String *string, s32 *output) {
	if (string == NULL || string->cstr == NULL || !string->len || output == NULL)
		return False;

	s32 buffer = 0;
	u32 power = 1;

	for (s32 i = string->len - 2; i >= 1; i--) {
		if (!isNum(string->cstr[i]))
			return False;

		buffer += charToNum(string->cstr[i]) * power;
		power *= 10;
	}

	if (string->cstr[0] == '-')
		buffer = -buffer;
	else if (isNum(string->cstr[0]))
		buffer += charToNum(string->cstr[0] * power);
	else if (string->cstr[0] != '+')
		return False;

	*output = buffer;

	return True;
}

b32 toString(String *string, const s32 val) {
    if (string == NULL)
        return False;

    s32 copy = val;
    u32 count;

    if (copy < 0) {
        count = 1;
        copy = -copy;
    }

    else {
        count = 0;
    }

    for (; copy; count++) {
        copy /= 10;
    }

    if (!count) {
        // Throw error?
        return False;
    }

    string->len = count + 1;
    string->cstr = (char *) calloc(string->len, sizeof(char));

    copy = val;
    count = 0;

    if (copy < 0) {
        copy = -copy;
        string->cstr[count++] = '-';
    }

    for (; copy; count++) {
        string->cstr[count] = (copy % 10) + 48;
        copy /= 10;
    }

    return True;
}

void constructString(String *string, const char *cstr) {
    if (string != NULL && cstr != NULL) {
        string->len = stringLength(cstr);
        string->cstr = (char *) calloc(string->len, sizeof(char));

        for (u32 i = 0; i < string->len; i++) {
            string->cstr[i] = cstr[i];
        }
    }
}

void desrtuctString(String *string) {
    if (string != NULL && string->len) {
        // free(string->cstr);
        myFree(string->cstr, "String");
        string->cstr = NULL;
        string->len = 0;
    }
}

void copyCString(String *string, const char *cstr) {
    if (string != NULL && cstr != NULL) {
        string->cstr = (char *) cstr;
        string->len = stringLength(cstr);
    }
}

void copyString(String *string, const String *src) {
    if (string != NULL && src != NULL) {
        string->cstr = src->cstr;
        string->len = src->len;
    }
}

void moveString(String *dest, String *src) {
    dest->cstr = src->cstr;
    src->cstr = NULL;
    dest->len = src->len;
    src->len = 0;
}

void appendCString(String *string, const char *cstr) {
    u32 len = 0;

    if (string != NULL && cstr != NULL && (len = stringLength(cstr))) {
        if (string->cstr == NULL && !string->len)
            copyCString(string, cstr);
        else {
            char *newStr = (char *) calloc(string->len + len - 1, sizeof(char));

            if (newStr == NULL) {
                // free(newStr);
                myFree(newStr, "Free'ing failed allocation");
                perror("Error allocating block of memory during string append!\n");
                exit(-1);
                return;
            }

            u32 i;
            for (i = 0; i < string->len - 1; i++) {
                newStr[i] = string->cstr[i];
            }

            for (u32 j = 0; j < len; j++) {
                newStr[i++] = cstr[j];
            }

            // Cleanup old string's memory.
            // free(string->cstr);
            myFree(string->cstr, "Free'ing string for appending");

            // Set string's pointer to point to new mem block.
            string->cstr = newStr;

            // New size is old len + len of cstr == 'i'.
            string->len = i;
        }
    }
}

#ifdef __cplusplus
}
#endif
