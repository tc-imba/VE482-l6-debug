//
//  lab4_dlist.c
//  ve482_lab6
//
//  Created by 朱宸 on 2017/11/27.
//  Copyright © 2017年 Charles. All rights reserved.
//

#include "lab4_dlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXLINE 1024
struct Node {
    char key[MAXLINE];
    dlistValue value;
    struct Node * next;
};

struct Head {
    dlistValueType type;
    struct Node * head;
};

dlist createDlist(dlistValueType type){
// EFFECTS: allocate and create a new dlist of datatype 'type' object
// returns the created dlist object on success
// returns NULL on error
    struct Head *head=(struct Head*) malloc(sizeof(struct Head));
    head->type=type;
    head->head=NULL;
    return head;
}

int dlistIsEmpty(dlist_const this){
// REQUIRES: argument 'this' is non-null and is a valid list
// EFFECTS: return whether the list 'this' is empty
    const struct Head* head=(const struct Head*) this;
    if (head->head!=NULL){
        return 0;
    }
    return 1;
}

void dlistAppend(dlist this, const char* key, dlistValue value){
// REQUIRES: type instantiated in 'value' corresponds to the datatype in the list
// argument 'this' and 'key' are both non-null and valid lists
// EFFECTS : add a line of form "key=value" to the tail of the dlist
// MODIFIES: modifies 'this'.
    struct Head *head=(struct Head*) this;
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    strcpy(node->key,key);
    if (head->type!= DLIST_STR){
        node->value=value;
        node->next=head->head;
    }
    else{
        node->value.strValue=(char *) malloc(sizeof(char[MAXLINE]));
        strcpy(node->value.strValue,value.strValue);
        node->next=head->head;
    }
    head->head=node;
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method){
// REQUIRES: argument 'this' is not null and is a valid list
// argument 'listDst' is not null and is a valid list
// EFFECTS: Sort 'listSrc' using method given by 'method'.
// Put the results in 'listDst' on success
// Leave 'listDst' unchanged on failure
// * Note 'listDst' may be non-empty when invoked.
// * Be very careful with memory management regarding string lists.
// MODIFIES: argument 'listDst'
    struct Head* tempList=createDlist(((struct Head*) this)->type);
    const struct Node* curr=((struct Head*) this)->head;
    int length=0;
    while (curr){
        dlistAppend(tempList, curr->key, curr->value);
        curr=curr->next;
        length++;
    }
    if (length==0) return;
    struct Node *current;
    struct Node *next;
    int i,j;
    char tempKey[MAXLINE];
    int k = length;
    srand((unsigned int) time(NULL) );
    if (method==DLIST_SORT_INC)
        for ( i = 0 ; i < length - 1 ; i++, k-- ) {
            current = tempList->head;
            next = current->next;
            for ( j = 1 ; j < k ; j++ ) {
                if (tempList->type==DLIST_STR){
                    if (strcmp(current->value.strValue,next->value.strValue)<0 ) {
                        char *tempValue=current->value.strValue;
                        current->value.strValue=next->value.strValue;
                        next->value.strValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                else if (tempList->type==DLIST_DOUBLE){
                    if (current->value.doubleValue<next->value.doubleValue) {
                        double tempValue=current->value.doubleValue;
                        current->value.doubleValue=next->value.doubleValue;
                        next->value.doubleValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                else if (tempList->type==DLIST_INT){
                    if (current->value.intValue<next->value.intValue) {
                        int tempValue=current->value.intValue;
                        current->value.intValue=next->value.intValue;
                        next->value.intValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                current = current->next;
                next = next->next;
            }
        }
    else if (method==DLIST_SORT_DEC)
        for ( i = 0 ; i < length - 1 ; i++, k-- ) {
            current = tempList->head;
            next = current->next;
            for ( j = 1 ; j < k ; j++ ) {
                if (tempList->type==DLIST_STR){
                    if (strcmp(current->value.strValue,next->value.strValue)>0 ) {
                        char *tempValue=current->value.strValue;
                        current->value.strValue=next->value.strValue;
                        next->value.strValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                else if (tempList->type==DLIST_DOUBLE){
                    if (current->value.doubleValue>next->value.doubleValue) {
                        double tempValue=current->value.doubleValue;
                        current->value.doubleValue=next->value.doubleValue;
                        next->value.doubleValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                else if (tempList->type==DLIST_INT){
                    if (current->value.intValue>next->value.intValue) {
                        int tempValue=current->value.intValue;
                        current->value.intValue=next->value.intValue;
                        next->value.intValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                current = current->next;
                next = next->next;
            }
        }
    else
        for ( i = 0 ; i < length - 1 ; i++, k-- ) {
            current = tempList->head;
            next = current->next;
            for ( j = 1 ; j < k ; j++ ) {
                if (tempList->type==DLIST_STR){
                    if (rand()%10 < 5 ) {
                        char *tempValue=current->value.strValue;
                        current->value.strValue=next->value.strValue;
                        next->value.strValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                else if (tempList->type==DLIST_DOUBLE){
                    if (rand()%10<5) {
                        double tempValue=current->value.doubleValue;
                        current->value.doubleValue=next->value.doubleValue;
                        next->value.doubleValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                else if (tempList->type==DLIST_INT){
                    if (rand()%10<5) {
                        int tempValue=current->value.intValue;
                        current->value.intValue=next->value.intValue;
                        next->value.intValue=tempValue;
                        strcpy(tempKey , current->key);
                        strcpy(current->key,next->key);
                        strcpy(next->key , tempKey);
                    }
                }
                current = current->next;
                next = next->next;
            }
        }
    if (((struct Head*)listDst)->head){
        dlistFree(listDst);
        listDst=tempList;
    }
    else {
        listDst=tempList;
    }
}

void dlistPrint(dlist_const this){
// REQUIRES: argument 'this' is not null and is a valid list
// EFFECTS: Print the content of 'this' in the required format to standard output.
// A newline must be followed after each line (including the last one).
    struct Node *curr= ((struct Head*) this)->head;
    while (curr){
        if(((struct Head*) this)->type==DLIST_INT){
            printf("%s=%d\n",curr->key,curr->value.intValue);
        }
        if(((struct Head*) this)->type==DLIST_DOUBLE){
            printf("%s=%f\n",curr->key,curr->value.doubleValue);
        }
        if(((struct Head*) this)->type==DLIST_STR){
            printf("%s=%s\n",curr->key,curr->value.strValue);
        }
        curr=curr->next;
    }
}



void dlistFree(dlist this){
// REQUIRES: argument 'this' is <EITHER> NULL or a valid list
// EFFECTS: if 'this' is NULL do nothing, other wise frees the list
// By freeing the list the user also needs to free the data
// the list manages
    if (this){
        struct Node* current=((struct Head*) this)->head;
        struct Node* head=current;
        while (head!=NULL){
            current=current->next;
            if (((struct Head*) this)->type==DLIST_STR){
                free(head->value.strValue);
            }
            free(head);
            head=current;
        }
        free(this);
    }
    return;
}




