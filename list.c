#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {

    List* nl = (List *) malloc(sizeof(List));
    nl->head = NULL;
    nl->tail = NULL;
    nl->current = NULL;

    return nl;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    return list->head;
}

void * nextList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->next == NULL) return NULL;
    list->current = list->current->next; 
    return list->current;
}

void * lastList(List * list) {

    if(list->tail == NULL) return NULL;

    return list->tail;
}

void * prevList(List * list) {
    if(list->current->prev == NULL) return NULL;
    list->current = list->current->prev; 
    return list->current;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    newNode->prev = NULL;
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}