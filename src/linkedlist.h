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

void constructLinkedList(LinkedList *);
void destructLinkedList(LinkedList *);

void addLinkedList(LinkedList *, void *);

void clearLinkedList(LinkedList *);

void constructLinkedListIter(LinkedListIter *, const LinkedList *, const b32);
void destructLinkedListIter(LinkedListIter *);

b32 hasNextLinkedListIter(const LinkedListIter *);
b32 hasPrevLinkedListIter(const LinkedListIter *);
void *nextLinkedListIter(LinkedListIter *);
void *prevLinkedListIter(LinkedListIter *);

#endif //MAKEFILEGENERATOR_LINKEDLIST_H
