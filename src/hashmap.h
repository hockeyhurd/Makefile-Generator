/**
 * HashMap header.
 *
 * @author hockeyhurd
 * @version 9/15/18
 */

#pragma once

#ifndef MAKEFILEGENERATOR_HASHMAP_H
#define MAKEFILEGENERATOR_HASHMAP_H

#include "types.h"

typedef struct HashMap {
    void *block;
    pint len;
} HashMap;

#endif //MAKEFILEGENERATOR_HASHMAP_H
