//
// Created by 季星佑 on 2017/11/28.
//

#include "list.h"
#include "sort.h"
#include "writeFile.h"
#include "stdio.h"

int (*mode[3][3])(void *, void *)={{INT_INC, INT_DEC, Random}, {DOUBLE_INC, DOUBLE_DEC, Random},
                                   {STRING_INC, STRING_DEC, Random}};//select the parameter for the qsort function

void (*print_mode[3])(FILE *file, void *)={INT_print, DOUBLE_print, STRING_print};//select the printing mode

dlist createDlist(dlistValueType type) {
  if (type <= 0x03 && type >= 0x01) {
    List *l;
    init(&l);
    l->type = type;
    setData(l->D, type == 0x01?0:type == 0x02?1:type == 0x03?2:3);
    return l;
  }
}

int dlistIsEmpty(dlist_const this) {
  return ((List *)this)->len?0:1;
}

void dlistAppend(dlist this, const char *key, dlistValue value) {
  this=(dlist)lappend(this,key,value);
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
  if (!dlistIsEmpty(this)) {
    setType(((List *)this)->T, method == 0x01?2:method == 0x02?0:method == 0x03?1:3);
    lsort(this, listDst, (int (*)(const void *, const void *))mode[((List *)this)->D.d][((List *)this)->T.t]);
  }
}

void dlistPrint(dlist_const this) {
  if (!dlistIsEmpty(this)) {
    List* tmp = this;
    lprint(this, stdout, print_mode[((const List *)this)->D.d]);
  }
}

void dlistFree(dlist this) {
  if (dlistIsEmpty(this)) {
    list_free(this);
  }
}