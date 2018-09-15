/**
 * LinkedList.c
 *
 * @author hockeyhurd
 * @version 9/15/18
 */

#include "linkedlist.h"

static LLNode *createNode(void *, LLNode *, LLNode *);
static void deleteNode(LLNode **);

LLNode *createNode(void *value, LLNode *next, LLNode *prev) {
    LLNode *node = (LLNode *) myMalloc(sizeof(LLNode), "malloc LLNode");

    node->value = value;
    node->next = next;
    node->prev = prev;

    return node;
}

void deleteNode(LLNode **node) {
    (*node)->value = NULL;
    (*node)->next = (*node)->prev = NULL;
    myFree(*node, "Free LLNode");
    *node = NULL;
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

b32 removeLinkedList(LinkedList *list, void *valueToFind, CmpFunc func) {
    if (list == NULL || list->len == 0)
        return False;

    LinkedListIter findResult = containsLinkedList(list, valueToFind, func);

    if (findResult.current == NULL)
        return False;
    else if (list->len == 1) {
        list->head = list->tail = NULL;

        deleteNode(&findResult.current);
        list->len--;
        return True;
    }

    if (findResult.current == list->head) {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    else if (findResult.current == list->tail) {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    // Somewhere in between.
    else {
        LLNode *prev = findResult.current->prev;
        LLNode *next = findResult.current->next;

        prev->next = next;
        next->prev = prev;
    }

    deleteNode(&findResult.current);

    // Check len after removal and fix ends as needed!

    list->len--;

    return True;
}

LinkedListIter containsLinkedList(const LinkedList *list, void *valueToFind, CmpFunc func) {
    LinkedListIter iter;
    constructLinkedListIter(&iter, list, True);

    while (hasNextLinkedListIter(&iter)) {
        // void *value = nextLinkedListIter(&iter);
        void *value = iter.current->value;

        if (func(value, valueToFind) == 0) {
            return iter;
        }

        nextLinkedListIter(&iter);
    }

    destructLinkedListIter(&iter);

    return iter;
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
