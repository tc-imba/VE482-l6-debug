#include "dlist.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct value
{
	char *val_char;
	dlistValue val_other;
} value_t;

typedef struct node
{
	struct value val;
	struct node *next;
} node_t;

typedef struct list
{
	node_t *head;
	node_t *curr;
	int list_length;
	dlistValueType type;
	node_t nd[1024];
} list_t;


dlist createDlist(dlistValueType type) {
	if (type == 0x00)
		return NULL;
	list_t *lists = (list_t*)malloc(sizeof(list_t));
	if (lists == NULL)
		return NULL;
	lists->head = NULL;
	lists->curr = NULL;
	lists->list_length = 0;
	lists->type = type;

	return lists;
}

int dlistIsEmpty(dlist_const this) {
	if (((list_t *)this)->list_length == 0)
		return 1;
	else
		return 0;
}

void dlistAppend(dlist this, const char* key, dlistValue value) {
	if (((list_t*)this)->head == NULL) {
		node_t *pt = (node_t*)malloc(sizeof(node_t));
		if (pt == NULL) {
			printf("Node creation failed!\n");
			return;
		}
		pt->val.val_char = key;
		pt->val.val_other = value;
		pt->next = NULL;
		((list_t*)this)->curr = pt;
		((list_t*)this)->head = pt;
		((list_t*)this)->list_length = 0;

		return;
	}

	node_t *pt = (node_t*)malloc(sizeof(node_t));
	if (pt == NULL) {
		printf("Node creation failed!\n");
		return;
	}
	pt->val.val_char = key;
	pt->val.val_other = value;
	pt->next = NULL;

	((list_t*)this)->curr->next = pt;
	((list_t*)this)->curr = pt;
	//((list_t*)this)->list_length = ((list_t*)this)->list_length+1;
	return;
}

int int_inc(const void *a, const void *b) {
	if ( (((node_t*)a)->val.val_other.intValue) > (((node_t*)b)->val.val_other.intValue) )
		return 1;
	else
		return -1;
}

int int_dec(const void *a, const void *b) {
	if ( (((node_t*)a)->val.val_other.intValue) < (((node_t*)b)->val.val_other.intValue) )
		return 1;
	else
		return -1;
}

int double_inc(const void *a, const void *b) {
	if ( (((node_t*)a)->val.val_other.doubleValue) > (((node_t*)b)->val.val_other.doubleValue) )
		return 1;
	else
		return -1;
}

int double_dec(const void *a, const void *b) {
	if ( (((node_t*)a)->val.val_other.doubleValue) < (((node_t*)b)->val.val_other.doubleValue) )
		return 1;
	else
		return -1;
}

int str_inc(const void *a, const void *b) {
	if ( strcmp((((node_t*)a)->val.val_other.strValue), (((node_t*)b)->val.val_other.strValue)) > 0 )
		return 1;
	else 
		return -1;
}

int str_dec(const void *a, const void *b) {
	if ( strcmp((((node_t*)a)->val.val_other.strValue), (((node_t*)b)->val.val_other.strValue)) < 0 )
		return 1;
	else 
		return -1;
}

int ran(const void *a, const void *b) {
	srand(time(NULL));
	if (rand() % 10000 < 5000)
		return 1;
	else
		return -1;
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
	node_t *temp = ((list_t*)this)->head;
	for (int s = 0; s < ((list_t*)this)->list_length; s++) {
		((list_t*)this)->nd[s] = *temp;
		temp = temp->next;
	}
	if (((list_t*)this)->type == 0x01) {
		if (method == 0x02) 
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), int_inc);
		else if (method == 0x03)
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), int_dec);
		else if (method == 0x01)
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), ran);
	}
	else if (((list_t*)this)->type == 0x03) {
		if (method == 0x02) 
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), double_inc);
		else if (method == 0x03)
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), double_dec);
		else if (method == 0x01)
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), ran);
	}
	else if (((list_t*)this)->type == 0x02) {
		if (method == 0x02) 
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), str_inc);
		else if (method == 0x03)
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), str_dec);
		else if (method == 0x01)
			qsort(((list_t*)this)->nd, ((list_t*)this)->list_length, sizeof(node_t), ran);
	}
	for (int j = 0; j < ((list_t*)this)->list_length; j++) {
		int k=1;
		k=strlen(((list_t*)this)->nd[j].val.val_char);
		char *addchar = (char*)malloc(sizeof(char)*k);

		memset(addchar,'\0',sizeof(char)*k);
		memcpy(addchar, ((list_t*)this)->nd[j].val.val_char, k);
		if (((list_t*)this)->type == 0x02){
			char *addvalue = (char*)malloc(sizeof(char)*1024);
			memcpy(addvalue,((list_t*)this)->nd[j].val.val_other.strValue,strlen(((list_t*)this)->nd[j].val.val_other.strValue)+1);
			dlistValue value1;
			value1.strValue = addvalue;
			dlistAppend(listDst,addchar,value1);
		}
		else dlistAppend(listDst, addchar, ((list_t*)this)->nd[j].val.val_other);
		
		
	}
}

void dlistPrint(dlist_const this) {
	int i;
	node_t *pt = ((list_t*)this)->head;
	while (pt != NULL) {
		if (((list_t*)this)->type == 0x01) {
			printf("%s=%d\n", pt->val.val_char, pt->val.val_other.intValue);
		}
		else if (((list_t*)this)->type == 0x03) {
			printf("%s=%f\n", pt->val.val_char, pt->val.val_other.doubleValue);
		}
		else if (((list_t*)this)->type == 0x02) {
			printf("%s=%s\n", pt->val.val_char, pt->val.val_other.strValue);
		}
		pt = pt->next;
	}

}


void dlistFree(dlist this) {
	node_t *temp = ((list_t*)this)->head;
	for (int n = 0; n < ((list_t*)this)->list_length; n++) {

		temp = temp->next;
		free(((list_t*)this)->head->val.val_char);

		if (((list_t*)this)->type == 0x02) 
			free(((list_t*)this)->head->val.val_other.strValue);

		free(((list_t*)this)->head);

		((list_t*)this)->head = temp;
	}
	free(((list_t*)this));
}


