/**
 * LinkedList.h
 *
 * @author hockeyhurd
 * @version 9/15/18
 */

#pragma once

#ifndef MAKEFILEGENERATOR_LINKEDLIST_H
#define MAKEFILEGENERATOR_LINKEDLIST_H

#include "types.h"

typedef struct LLNode LLNode;

struct LLNode {
    void *value;
    LLNode *next;
    LLNode *prev;
};

typedef struct LinkedList {
    LLNode *head;
    LLNode *tail;
    pint len;
} LinkedList;

typedef struct LinkedListIter {
    LLNode *current;
} LinkedListIter;

typedef s32 (*CmpFunc)(void *, void *);

void constructLinkedList(LinkedList *);
void destructLinkedList(LinkedList *);

void addLinkedList(LinkedList *, void *);
b32 removeLinkedList(LinkedList *, void *, CmpFunc);

LinkedListIter containsLinkedList(const LinkedList *, void *, CmpFunc);

void clearLinkedList(LinkedList *);

void constructLinkedListIter(LinkedListIter *, const LinkedList *, const b32);
void destructLinkedListIter(LinkedListIter *);

b32 hasNextLinkedListIter(const LinkedListIter *);
b32 hasPrevLinkedListIter(const LinkedListIter *);
void *nextLinkedListIter(LinkedListIter *);
void *prevLinkedListIter(LinkedListIter *);

#endif //MAKEFILEGENERATOR_LINKEDLIST_H
