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

#pragma once

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <cstdlib>

#ifdef __APPLE__
#define OS_APPLE 1
#define OS_WIN 0
#define OS_UNIX 1
#elif WIN32 || _WIN64
#define OS_APPLE 0
#define OS_WIN 1
#define OS_UNIX 0
#elif __unix__
#define OS_APPLE 0
#define OS_WIN 0
#define OS_UNIX 1
#endif

#ifdef _DEBUG
#define Debug 1
#else 
#define Debug 0
#endif

#if Debug
#define global_status 
#else
#define global_status static
#endif

#if 0
#ifndef internal
#define internal static
#endif
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef u32 b32;
typedef size_t pint;

typedef float f32;
typedef double f64;

typedef s32(*CompareFunc)(void *, void *);

#ifndef False
#define False (b32) 0u
#endif

#ifndef True
#define True (b32) 1u
#endif

#if 0
#ifdef __cplusplus
extern "C" {
#endif
#endif

u32 myPow(const u32, const u32);

void *myMalloc(const u32, const char *);
void myFree(void *, const char *);

void copyBytes(char *, char *, const u32, const u32, const u32);

#if 0
#ifdef __cplusplus
}
#endif
#endif

#endif
