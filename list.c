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
    if(list->head != NULL)
    {
        list->current = list->head;
        return list->head->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->next == NULL) return NULL;
    list->current = list->current->next; 
    return list->current->data;
}

void * lastList(List * list) {

    if(list->tail == NULL) return NULL;

    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->prev == NULL) return NULL;
    list->current = list->current->prev; 
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    newNode->prev = NULL;
    newNode->next = list->head;
    if(list->head != NULL) list->head->prev = newNode;
    list->head = newNode;
    if(list->tail == NULL) list->tail= newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {

    // creamos nuevo nodo con datos respectivos
    Node* newNode = createNode(data);
    
    if(list->head == NULL && list->tail == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        list->current = newNode;
        return;
    }
    if(list->current != NULL)
    {
        if(list->current->next == NULL)
        {
            list->current->next = newNode;
            list->tail = newNode;
            newNode->next = NULL;
            newNode->prev = list->current;
            list->current = newNode;
            return;
            // tail
        }   
        if(list->current->next != NULL)
        {
            newNode->next = list->current->next;
            newNode->prev = list->current;
            list->current->next->prev = newNode;
            list->current->next = newNode;
            list->current = newNode;
            return;
        }
    }
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

    // si la lista esta vacia
    if(list->head == NULL || list->current == NULL) return NULL;
    
    // si el nodo es head
    if(list->head == list->current)
    {
        list->head = list->current->next;
        list->current->next->prev = NULL;
    }

    // si el nodo es tail
    if(list->current == list->tail)
    {
        list->tail = list->current->prev;
        list->current->prev->next = NULL;
    }

    // si el nodo no es head ni tail
    if(list->current->next != NULL && list->current->prev != NULL)
    {
        list->current->next->prev = list->current->prev;
        list->current->prev->next = list->current->next;
    }

    // creamos una copia del puntero data antes de liberar memoria
    void * aux = list->current->data;

    free(list->current);

    return aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}