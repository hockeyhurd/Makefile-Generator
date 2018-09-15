/**
 * HashMap header.
 *
 * @author hockeyhurd
 * @version 9/15/18
 */

#pragma once

#ifndef MAKEFILEGENERATOR_HASHMAP_H
#define MAKEFILEGENERATOR_HASHMAP_H

#include "linkedlist.h"

typedef struct HashMap {
    LinkedList *list;
    u32 numBuckets;
    f32 loadFactor;
    pint len;
} HashMap;

typedef pint (*HashFunc)(void *);

void constructHashMap(HashMap *, const u32, const f32);
void destructHashMap(HashMap *);

void putHashMap(HashMap *, void *, void *, HashFunc);

#endif //MAKEFILEGENERATOR_HASHMAP_H
