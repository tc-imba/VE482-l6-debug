//
//  list.h
//  lab4_1
//
//  Created by 季星佑 on 2017/10/25.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dlist.h"
#include "readName.h"

typedef struct tagNode {
  dlistValue data;
  char *c;
  void *v;
  struct tagNode *next;
}Node;

typedef struct tagList {
  Node *first, *last;
  dlistValueType type;
  Data D;
  Type T;
  ssize_t len;
}List;

void init(List **l);

void list_free(List *l);

List *lappend(List *l, char *str, dlistValue data);

void lsort(List *l, List *ll, int (*cmp)(const void *, const void *));

void lprint(List *l, FILE *f, void(*print_mode)(FILE* f, void *));

#endif /* list_h */
