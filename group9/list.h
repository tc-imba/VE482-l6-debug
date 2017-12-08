#ifndef VE482H3_LIST_H
#define VE482H3_LIST_H

#include <stdio.h>
#include "lab4_dlist.h"

typedef struct node
{
    char *str;
    struct node *next;
    dlistValue value;
}node_t;

typedef struct dlist
{
    struct node *f;
    struct node *ff;
    dlistValueType type;
    size_t size;
}dlist_t;

void createList(dlist_t **list);

node_t *createNode(dlist_t *list, char *str, dlistValue value);

void sortList(dlist_t *list, dlist_t *tempList, int (*sss)(const void *a, const void *b));

void printList(const dlist_t *list,FILE *write);

void append(dlist_t *list, char *str, dlistValue value);

void freeNode(dlist_t *list,node_t *node);

void freeList(dlist_t *list);

#endif //VE482H3_LIST_H
