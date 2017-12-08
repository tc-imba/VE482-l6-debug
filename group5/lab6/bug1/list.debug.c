//
//  list.c
//  
//
//  Created by Cheng on 2017/11/28.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_OF_CHAR 1024
#define NUM_of_N 128

#include "list.h"



void addNode(const char* newname, dlistValue newvalue, list* Llist)
{
    ++Llist->num;
    char *New_name = malloc(strlen(newname) + 1);
    node* nd=(node*)malloc(NUM_of_N*sizeof(node));
    nd->next=Llist->first;
    strcpy(New_name, newname);
    nd->name=New_name;
    if (Llist->type == DLIST_STR)
    {
        char *value_s= malloc(strlen(newvalue.strValue) + 1);
        strcpy(value_s, newvalue.strValue);
        nd->value.strValue = value_s;
    }
    else
        nd->value=newvalue;
    Llist->first=nd;
}

node* searchNode(const char* name, list* Llist)
{
    if(Llist->first->next==NULL) return NULL;
    else
    {
        char* currentName=Llist->first->name;
        if(strcmp(currentName, name)==0)
            return Llist->first;
        else
        {
            Llist->first=Llist->first->next;
            return searchNode(name, Llist);
        }
    }
}

list* sorting(list* Llist, int(*fn)(dlistValue, dlistValue, int),  int type)
{
    for (node* i=Llist->first; i->next!=NULL; i=i->next)
    {
        for (node* j=i->next; j->next!=NULL; j=j->next)
        {
            if (fn(i->value,j->value,type)==1)
            {
                char* t_n=i->name;
                dlistValue t_v=i->value;
                i->name=j->name;
                i->value=j->value;
                j->name=t_n;
                j->value=t_v;
            }
        }
    }
    return Llist;
}



int inc(dlistValue data_a, dlistValue data_b, int type)
{
    if(type==0)
    {
        char *valueA_s = malloc(strlen(data_a.strValue) + 1);
        char *valueB_s = malloc(strlen(data_b.strValue) + 1);
        if (strcmp(valueA_s, valueB_s)>=0)
            return 1;
        else
            return 0;
    }
    else if(type==1)
    {
        if (data_a.intValue>=data_b.intValue)
            return 1;
        else
            return 0;
    }
    else
    {
        if (data_a.doubleValue>=data_b.doubleValue)
            return 1;
        else
            return 0;
    }
}

int dec(dlistValue data_a, dlistValue data_b, int type)
{
    if(type==0)
    {
        char *valueA_s = malloc(strlen(data_a.strValue) + 1);
        char *valueB_s = malloc(strlen(data_b.strValue) + 1);
        if (strcmp(valueA_s, valueB_s)>=0)
            return 0;
        else
            return 1;
    }
    else if(type==1)
    {
        if (data_a.intValue>=data_b.intValue)
            return 0;
        else
            return 1;
    }
    else
    {
        if (data_a.doubleValue>=data_b.doubleValue)
            return 0;
        else
            return 1;
    }
}

void choosingSort(list* this,list* listDst,dlistSortMethod method)
{
    if (method==DLIST_SORT_INC)
        listDst=sorting(this, inc, method);
    else if(method==DLIST_SORT_DEC)
        listDst=sorting(this, dec, method);
}

void ListFree(list* Llist)
{
    
}

void printlist(list* Llist)
{
    dlistValueType Type=Llist->type;
    if (Type==DLIST_STR)
    {
        while (Llist->first!=NULL)
        {
            printf("%s=%s\n", Llist->first->name, (char*)Llist->first->value.strValue);
            Llist->first=Llist->first->next;
        }
    }
    
    else if (Type==DLIST_INT)
    {
        
        while (Llist->first!=NULL)
        {
            printf("%s=%d\n", Llist->first->name, Llist->first->value.intValue);
            
            Llist->first=Llist->first->next;
        }
    }
    
    else if (Type==DLIST_DOUBLE)
    {
        while (Llist->first!=NULL)
        {
            printf("%s=%f\n", Llist->first->name, Llist->first->value.doubleValue);
            Llist->first=Llist->first->next;
        }
    }
}

void listCopy(const list* old, list* new)
{
    
    new->first=old->first;
    new->num=old->num;
    new->type=old->type;
    
}
    
    
    


