#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct node node;

typedef struct {
    node *head;
    node *tail;
    size_t size;
} dll;


struct node{
    node *next;
    node *previous;
    char *charptr;
    void *voidptr;
};



void dll_ctor(dll *list);

void dll_dtor(dll *list);

void swap(dll *list, node* x, node* y);

void push_back(dll *list, char *string, void *input);

void sort(dll *list, int type, int out_type);

node *find(dll *list, void *query, int type);


#endif // LIST_H_INCLUDED
