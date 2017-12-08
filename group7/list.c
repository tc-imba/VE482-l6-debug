//
//  list.c
//  lab4_1
//
//  Created by 季星佑 on 2017/10/25.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#include "list.h"

void init(List **l) {
  *l = malloc(sizeof(List));
  Node *temp = malloc(sizeof(Node));
  temp->c = NULL;
  temp->v = 0;
  (*l)->first = NULL;
  (*l)->last = NULL;
  (*l)->len = 0;
}

void list_free(List *l) {
  l->first=NULL;
  l->last=NULL;
  l->len=0;
  free(l);
}

List *lappend(List *l, char *str, dlistValue data) {
  Node *new_node = malloc(sizeof(Node));
  new_node->c = str;
  new_node->data = data;
  new_node->v = (void*)&(new_node->data);
  l->len++;
  if (l->last) {
    l->last->next=new_node;
    l->last=new_node;
  } else {
    l->first=new_node;
    l->last=new_node;
  }
  l->last = new_node;
  return l;
}

void lsort(List *l, List *ll, int (*cmp)(const void *, const void *)) {
  if (l->len == 0) {
    return;
  }
  Node *arr = malloc(sizeof(Node)*l->len);
  Node *temp = l->first;
  for (int i = 0; i < l->len; ++i) {
    memcpy(arr + i, temp, sizeof(Node));
    temp = temp->next;
  }
  qsort(arr, (size_t)l->len, sizeof(Node), cmp);
  for (int i = 0; i < l->len; ++i) {
    lappend(ll, arr[i].c, arr[i].data);
  }
  free(arr);
}

void lprint(List *l, FILE *f, void(*print_mode)(FILE *f, void *)) {
  Node *N;
  N = l->first;
  for (int i = 0; i < l->len; ++i) {
    fprintf(f, "%c=", *(N->c));
    dlistValue* tmp = (dlistValue*)N->v;
    print_mode(f, N->v);
    fprintf(f, "\n");
    N = N->next;
  }
}