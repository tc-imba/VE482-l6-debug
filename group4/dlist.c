#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

dlist createDlist(dlistValueType type) {
    list* d = (list*)malloc(sizeof(list));
    d->type = type;
    d->first = NULL;
    d->last = NULL;
    return (dlist)d;
}

void dlistAppend(dlist this, const char* key, dlistValue value) {
    node *cursor = ((list*)this)->first;
    if (cursor == NULL) {
        node* newnode = (node*)malloc(sizeof(node));
        newnode->str = key;
        newnode->data = value;
        newnode->prev = NULL;
        newnode->next = NULL;
        ((list*)this)->last = newnode;
    }
    else {
        node* newnode = (node*)malloc(sizeof(node));
        newnode->str = key;
        newnode->data = value;
        newnode->prev = ((list*)this)->last;
        newnode->next = NULL;
        ((list*)this)->last = newnode;
    }
    return;
}

void insertstart(list* dlist, char* str, dlistValue data)
{
    node *cursor=dlist->first;
    if(cursor==NULL)
    {
        node* newnode=(node*)malloc(sizeof(node));
        newnode->str=str;
        newnode->data=data;
        newnode->prev=NULL;
        newnode->next=NULL;
        dlist->first=newnode;
    }
    else
    {
        node* newnode=(node*)malloc(sizeof(node));
        newnode->str=str;
        newnode->data=data;
        newnode->next=dlist->first;
        newnode->prev=NULL;
        dlist->first=newnode;
    }
    return;
}
node* search(list* dlist, dlistValue data, char* str)
{
	dlistValueType type = dlist->type;
	int index = 0;
	node *cursor = dlist->first;
	if (cursor == NULL) return NULL;
	else {
        index = index+1;
        if (type == DLIST_STR) if (strcmp(cursor->data.strValue ,data.strValue) == 0 && strcmp(cursor->str,str) == 0) {return cursor;}
        if (type == DLIST_INT) if (cursor->data.intValue == data.intValue && strcmp(cursor->str,str) == 0) {return cursor;}
        if (type == DLIST_DOUBLE) if (cursor->data.doubleValue == data.doubleValue && strcmp(cursor->str,str) == 0) {return cursor;}

	}
	while (cursor->next != NULL) {
	    cursor = cursor->next;
	    index = index+1;
        if (type == DLIST_STR) if (strcmp(cursor->data.strValue, data.strValue) == 0&& strcmp(cursor->str,str) == 0) {return cursor;}
        if (type == DLIST_INT) if (cursor->data.intValue == data.intValue && strcmp(cursor->str,str) == 0) {return cursor;}
        if (type == DLIST_DOUBLE) if (cursor->data.doubleValue == data.doubleValue && strcmp(cursor->str,str) == 0) {return cursor;}
	}
	return NULL;
}
int dlistIsEmpty(dlist_const this) {
	if (((list*)this)->first == NULL) return 1;
	return 0;
}

void dlistPrint(dlist_const this) {
    if (((list*)this)->type == DLIST_STR) {
        node *cursor = ((list*)this)->first;
        while(cursor != ((list*)this)->last) {
            printf(cursor->str);
            printf(":%s\n", cursor->data.strValue);
            cursor=cursor->next;
        }
        printf(cursor->str);
        printf(":%s\n", cursor->data.strValue);
    }
    else if (((list*)this)->type == DLIST_INT) {
        node *cursor = ((list*)this)->first;
        while(cursor != ((list*)this)->last) {
            printf(cursor->str);
            printf(":%d\n", cursor->data.intValue);
            cursor=cursor->next;
        }
        printf(cursor->str);
        printf(":%d\n", cursor->data.intValue);
    }
    else if (((list*)this)->type == DLIST_DOUBLE) {
        node *cursor = ((list*)this)->first;
        while(cursor != ((list*)this)->last) {
            printf(cursor->str);
            printf(":%lf\n", cursor->data.doubleValue);
            cursor=cursor->next;
        }
        printf(cursor->str);
        printf(":%lf\n", cursor->data.doubleValue);
    }
}

void delet(list* dlist, dlistValue data, char* str)
{
    node* del=search(dlist,data,str);
    if(del->prev==NULL && del->next!=NULL)
    {
        dlist->first=del->next;
        dlist->first->prev=NULL;
    }
    else if(del->prev!=NULL && del->next==NULL)
    {
        dlist->last=del->prev;
        dlist->last->next=NULL;
    }
    else
    {
        del->prev->next=del->next;
        del->next->prev=del->prev;
    }
}
void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
    srand(time(NULL));
	void *newvoid;
	dlistValueType type = ((list*)this)->type;
	char* str;
	int randnum;
	list* templist = (list*)this;
	if (type == DLIST_STR) {
        char* a;
		if (method == DLIST_SORT_INC) {
			while (!dlistIsEmpty(templist)) {
			    node *cursor = templist->first;
				a = cursor->data.strValue;
				while (cursor->next != NULL) {
					cursor = cursor->next;
					if (strcmp(a, cursor->data.strValue) >= 0) {
                        a = cursor->data.strValue;
                        str = cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				dlistAppend((list*)listDst, str, (dlistValue)a);
			}
		}
		else if (method == DLIST_SORT_DEC) {
			while (!dlistIsEmpty(templist)) {
			    node *cursor = templist->first;
				a = cursor->data.strValue;
				while (cursor->next != NULL) {
					cursor = cursor->next;
					if (strcmp(a, cursor->data.strValue) >= 0) {
                        a = cursor->data.strValue;
                        str = cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				insertstart((list*)listDst,str,(dlistValue)a);
			}
		}
		else if (method == DLIST_SORT_RAND) {
			while (!dlistIsEmpty(templist)) {
			    node *cursor = templist->first;
				a = cursor->data.strValue;
				while (cursor->next!=NULL) {
					cursor=cursor->next;
					if (strcmp(a, cursor->data.strValue) >= 0) {
                        a = cursor->data.strValue;
                        str = cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				randnum = rand()%2;
				if (randnum == 0) {dlistAppend((list*)listDst,str,(dlistValue)a);}
				else {insertstart((list*)listDst,str,(dlistValue)a);}
			}
		}
    }
	else if (type == DLIST_INT) {
	    int a;
		if (method == DLIST_SORT_INC) {
			while (!dlistIsEmpty((void*)templist)) {
			    node *cursor = templist->first;
				a = cursor->data.intValue;
				while (cursor->next != NULL) {
					cursor = cursor->next;
					if (a > cursor->data.intValue) {
                        a = cursor->data.intValue;
                        str = cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				dlistAppend((list*)listDst,str,(dlistValue)a);
			}
		}
		else if (method == DLIST_SORT_DEC) {
			while (!dlistIsEmpty((void*)templist)) {
			    node *cursor = templist->first;
				a = cursor->data.intValue;
				while (cursor->next != NULL) {
					cursor = cursor->next;
					if (a > cursor->data.intValue) {
                        a = cursor->data.intValue;
                        str=cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				insertstart((list*)listDst,str,(dlistValue)a);
			}
		}
		else if (method == DLIST_SORT_RAND) {
			while (!dlistIsEmpty((void*)templist)) {
			    node *cursor = templist->first;
				a = cursor->data.intValue;
				while (cursor->next != NULL) {
					cursor = cursor->next;
					if (a > cursor->data.intValue) {
                        a = cursor->data.intValue;
                        str=cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				randnum = rand()%2;
				if (randnum==0) {insertstart((list*)listDst,str,(dlistValue)a);}
				else {dlistAppend((list*)listDst,str,(dlistValue)a);}
			}
		}
	}
	else if (type == DLIST_DOUBLE) {
        double a;
		if (method == DLIST_SORT_INC) {
			while (!dlistIsEmpty((void*)templist)) {
			    node *cursor = templist->first;
				a = cursor->data.doubleValue;
				while (cursor->next!=NULL) {
					cursor = cursor->next;
					if (a > cursor->data.doubleValue) {
                        a = cursor->data.doubleValue;
                        str = cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				dlistAppend((list*)listDst,str,(dlistValue)a);
			}
		}
		else if (method == DLIST_SORT_DEC) {
			while (!dlistIsEmpty((void*)templist)) {
			    node *cursor = templist->first;
				a = cursor->data.doubleValue;
				while (cursor->next!=NULL) {
					cursor = cursor->next;
					if (a > cursor->data.doubleValue) {
                        a = cursor->data.doubleValue;
                        str = cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				insertstart((list*)listDst,str,(dlistValue)a);
			}
		}
		else if (method == DLIST_SORT_RAND) {
			while (!dlistIsEmpty((void*)templist)) {
			    node *cursor=templist->first;
				a = cursor->data.doubleValue;
				while (cursor->next != NULL) {
					cursor = cursor->next;
					if (a > cursor->data.doubleValue) {
                        a = cursor->data.doubleValue;
                        str = cursor->str;
					}
				}
				delet(templist,(dlistValue)a,str);
				randnum=rand()%2;
				if (randnum==0) {insertstart((list*)listDst,str,(dlistValue)a);}
				else {dlistAppend((list*)listDst,str,(dlistValue)a);}
			}
		}
    }
}
void dlistFree(dlist this) {
	node *cursor = ((list*)this)->first;
	node *victim;
	while (cursor != ((list*)this)->last) {
		victim = cursor;
		((list*)this)->first = cursor->next;
		cursor->prev = NULL;
		free(victim);
		cursor=cursor->next;
	}
	victim =cursor;
	((list*)this)->first = NULL;
	((list*)this)->last = NULL;
	free(victim);
}
