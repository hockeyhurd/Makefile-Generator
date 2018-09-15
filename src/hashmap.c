/**
 * HashMap implementation.
 *
 * @author hockeyhurd
 * @version 9/15/18
 */

#include "hashmap.h"

typedef struct Pair {
    void *key;
    void *value;
} Pair;

static s32 pairCompare(void *leftPtr, void *rightPtr) {
    Pair *left = (Pair *) leftPtr;
    Pair *right = (Pair *) rightPtr;

    return (s32) (left->key == right->key /*&& left->value == right->value*/);
}

void constructHashMap(HashMap *map, const u32 numBuckets, const f32 loadFactor) {
    map->list = (LinkedList *) myMalloc(numBuckets * sizeof(LinkedList), "Malloc HashMap Internal Buffer");

    for (u32 i = 0; i < numBuckets; i++)
        constructLinkedList(&map->list[i]);

    map->numBuckets = numBuckets;
    map->loadFactor = loadFactor;
    map->len = 0;
}

void destructHashMap(HashMap *map) {
    for (u32 i = 0; i < map->numBuckets; i++) {
        destructLinkedList(&map->list[i]);
    }

    map->numBuckets = 0;
    map->loadFactor = 0.0;
    map->len = 0;
}

void putHashMap(HashMap *map, void *key, void *value, HashFunc func) {
    Pair pair;
    pair.key = key;
    pair.value = value;

    const pint hashIndex = func(key);
    LinkedList *list = &map->list[hashIndex];
    const LinkedListIter findResult = containsLinkedList(list, &pair, pairCompare);

    // Key already in mapping.
    if (findResult.current != NULL) {
        Pair *resultPair = (Pair *) findResult.current->value;
        resultPair->value = value;
    }

    // Else not found.
    else {
        Pair *pairToAdd = myMalloc(sizeof(Pair), "Malloc HashMap pair");
        addLinkedList(list, pairToAdd);
    }
}
