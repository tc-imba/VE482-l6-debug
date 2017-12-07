#ifndef DLIST_H
#define DLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum dlistValueType_t {
    DLIST_STR = 0x01, // list contains char* values
    DLIST_INT = 0x02, // list contains int values
    DLIST_DOUBLE = 0x03, // list contains double values
    DLIST_UNKOWN = 0x00,
} dlistValueType;

typedef enum dlistSortMethod_t {
    DLIST_SORT_INC = 0x01, // Sort in ascending order
    DLIST_SORT_DEC = 0x02, // Sort in descending order
    DLIST_SORT_RAND = 0x03, // Randomize entries
    DLIST_SORT_UNKOWN = 0x00,
} dlistSortMethod;

typedef union dlistValue_t {
    int intValue;
    double doubleValue;
    char* strValue;
} dlistValue;

typedef struct node {
	char* str;
	dlistValue data;
	struct node* next;
	struct node* prev;
} node;

typedef struct list{
    node* first;
    node* last;
    dlistValueType type;//0 for char, 1 for int, 2 for double
} list;

typedef void* dlist;
typedef const void* dlist_const;

dlist createDlist(dlistValueType type);
void dlistAppend(dlist this, const char* key, dlistValue value);
void insertstart(list* dlist, char* str, dlistValue data);
node* search(list* dlist, dlistValue data, char* str);
int dlistIsEmpty(dlist_const this);
void dlistPrint(dlist_const this);
void delet(list* dlist, dlistValue data, char* str);
void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method);
void dlistFree(dlist this);


#endif
