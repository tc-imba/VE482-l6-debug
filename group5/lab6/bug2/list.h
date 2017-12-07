//
//  list.h
//  
//
//  Created by Cheng on 2017/11/28.
//

#ifndef list_h
#define list_h

#include <stdio.h>
#include "dlist.h"

typedef struct node
{
    struct node* next;
    dlistValue value;
    char* name;
}node;

typedef struct list
{
    node* first;
    dlistValueType type;
    int num;
}list;

char *readLine(FILE *fd);
void addNode(const char* newname, dlistValue newvalue, list* Llist);
node* searchNode(const char* name, list* Llist);
void ListFree(list* Llist);
list* sorting(list* Llist, int(*fn)(dlistValue, dlistValue, int), int type);
int inc(dlistValue data_a, dlistValue data_b, int type);
int dec(dlistValue data_a, dlistValue data_b, int type);
list* choosingSort(list* this,list* listDst,dlistSortMethod method);
void printlist(list* Llist);
void listCopy(const list* old, list* new);
#endif /* list_h */


