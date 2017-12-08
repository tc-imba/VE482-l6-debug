#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab4_dlist.h"
#include "list.h"

int incInt(const void *a,const void *b)
{
    return ((node_t *)a)->value.intValue-((node_t *)b)->value.intValue;
}

int decInt(const void *a,const void *b)
{
    return ((node_t *)b)->value.intValue-((node_t *)a)->value.intValue;
}

int incDouble(const void *a,const void *b)
{
    return (((node_t *)a)->value.doubleValue-((node_t *)b)->value.doubleValue>0)?1:-1;
}

int decDouble(const void *a,const void *b)
{
    return (((node_t *)b)->value.doubleValue-((node_t *)a)->value.doubleValue>0)?1:-1;
}

int incString(const void *a,const void *b)
{
    return strcmp(((node_t *)a)->value.strValue,((node_t *)b)->value.strValue);
}

int decString(const void *a,const void *b)
{
    return strcmp(((node_t *)b)->value.strValue,((node_t *)a)->value.strValue);
}

int ran(const void *a, const void *b)
{
    return rand()%3-1;
}

static int (*const sss[7])(const void *,const void *)={incInt,decInt,incDouble,decDouble,incString,decString,ran};

dlist createDlist(dlistValueType type)
{
    if (type<=DLIST_DOUBLE&&type>DLIST_UNKOWN)
    {
        dlist_t *list;
        createList(&list);
        list->type=type;
        return list;
    }
    return NULL;
}

int dlistIsEmpty(dlist_const this)
{
    return ((const dlist_t *) this)->size == 0;
}

void dlistAppend(dlist this, const char *key, dlistValue value)
{
    append(this,key,value);
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method)
{
    dlistValueType type=((const dlist_t*)(this))->type;
    if (method<=DLIST_SORT_UNKOWN||method>DLIST_SORT_DEC)
        return;
    if (type<=DLIST_UNKOWN||type>DLIST_DOUBLE)
        return;
    dlist_t *list=(dlist_t*)(listDst);
    while (list->f!=NULL)
    {
        node_t *toClear=list->f;
        list->f=toClear->next;
        freeNode(list,toClear);
    }
    list->f=list->ff=NULL;
    list->size=0;
    int cmpIndex;
    if (type==DLIST_INT&&method==DLIST_SORT_INC) cmpIndex=0;
    else if (type==DLIST_INT&&method==DLIST_SORT_DEC) cmpIndex=1;
    else if (type==DLIST_DOUBLE&&method==DLIST_SORT_INC) cmpIndex=2;
    else if (type==DLIST_DOUBLE&&method==DLIST_SORT_DEC) cmpIndex=3;
    else if (type==DLIST_STR&&method==DLIST_SORT_INC) cmpIndex=4;
    else if (type==DLIST_STR&&method==DLIST_SORT_DEC) cmpIndex=5;
    else cmpIndex=6;
    sortList((dlist_t*)this,listDst,sss[cmpIndex]);
}

void dlistPrint(dlist_const this)
{
    printList(this,stdout);
}

void dlistFree(dlist this)
{
    freeList(this);
}