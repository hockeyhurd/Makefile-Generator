/**
 * LinkedList.c
 *
 * @author hockeyhurd
 * @version 9/15/18
 */

#include "linkedlist.h"

static LLNode *createNode(void *, LLNode *, LLNode *);

LLNode *createNode(void *value, LLNode *next, LLNode *prev) {
    LLNode *node = (LLNode *) myMalloc(sizeof(LLNode), "malloc LLNode");

    node->value = value;
    node->next = next;
    node->prev = prev;

    return node;
}

void constructLinkedList(LinkedList *list) {
    list->head = list->tail = NULL;
    list->len = 0;
}

void destructLinkedList(LinkedList *list) {
    clearLinkedList(list);
}

void addLinkedList(LinkedList *list, void *value) {
    if (list->len == 0) {
        list->head = createNode(value, NULL, NULL);
    }

    else if (list->len == 1) {
        list->tail = createNode(value, NULL, list->head);
        list->head->next = list->tail;
    }

    else {
        LLNode *node = createNode(value, NULL, list->tail);
        list->tail->next = node;
        list->tail = node;
    }

    list->len++;
}

void clearLinkedList(LinkedList *list) {
    if (list == NULL || !list->len)
        return;

    LLNode *del = list->head;

    while (del != NULL) {
        list->head = list->head->next;
        myFree(del, "free LLNode");
        del = list->head;
    }

    del = NULL;
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

void constructLinkedListIter(LinkedListIter *iter, const LinkedList *list, const b32 startAtHead) {
    if (startAtHead)
        iter->current = list->head;
    else
        iter->current = list->tail;
}

void destructLinkedListIter(LinkedListIter *iter) {
    iter->current = NULL;
}

b32 hasNextLinkedListIter(const LinkedListIter *iter) {
    return (b32) (iter != NULL && iter->current != NULL /*&& iter->current->next != NULL*/);
}

b32 hasPrevLinkedListIter(const LinkedListIter *iter) {
    return (b32) (iter != NULL && iter->current != NULL /*&& iter->current->prev != NULL*/);
}

void *nextLinkedListIter(LinkedListIter *iter) {
    void *result = iter->current->value;
    iter->current = iter->current->next;

    return result;
}

void *prevLinkedListIter(LinkedListIter *iter) {
    void *result = iter->current->value;
    iter->current = iter->current->prev;

    return result;
}
