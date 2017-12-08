#include "lab4_dlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    char* key;
    dlistValue value;
    struct node* next;
    struct node* prev;
};

struct linkedList {
    int size;
    struct node* head;
    struct node* tail;
    dlistValueType type;
};

int compLarge(const struct node* node1, const struct node* node2, dlistValueType type);
int compSmall(const struct node* node1, const struct node* node2, dlistValueType type);

dlist createDlist(dlistValueType type) {
    // EFFECTS: allocate and create a new dlist of datatype ' type ' object
    // returns the created dlist object on success
    // returns NULL on error
    struct linkedList* list = (struct linkedList*)malloc(sizeof(struct linkedList)*MAXLINENUM);
    list->size = 0;
    list->head = list->tail = NULL;
    list->type = type;
    return list;
}


int dlistIsEmpty(dlist_const this) {
    // REQUIRES: argument ' this ' is non-null and is a valid list
    // EFFECTS: return whether the list ' this ' is empty
    struct linkedList* list = (struct linkedList*)this;
    return (list->size == 0);
}

void dlistAppend(dlist this, const char* key, dlistValue value) {
    // REQUIRES: type instantiated in ' value ' corresponds to the datatype in the list
    //
    // EFFECTS : add a line of form ”key=value�?to the tail of the dlist
    // MODIFIES: modifies ' this ' .
    struct linkedList* list = (struct linkedList*)this;
    struct node* tnode = (struct node*)malloc(sizeof(struct node));
    tnode->key = key;
    tnode->value = value;
    if (dlistIsEmpty(list)) {
        list->head = list->tail = tnode;
        tnode->prev = NULL;
        tnode->next = NULL;
    }
    else {
        list->tail->next = tnode;
        tnode->prev = list->tail;
        tnode->next = NULL;
        list->tail = tnode;
    }
    list->size++;
    this = list;
    //printf("length: %d\n", list->size);
    //dlistPrint(list);
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
    // REQUIRES: argument ' this ' is not null and is a valid list
    // EFFECTS: Sort ' listSrc ' using method given by ' method ' .
    // Put the results in ' listDst ' on success
    // Leave ' listDst ' unchanged on failure
    // * Note ' listDst ' may be non-empty when invoked.
    // * Be very careful with memory management regarding string lists.
    // MODIFIES: argument ' listDst 'argument ' listDst ' is not null and is a valid list
    struct linkedList* list = (struct linkedList*)this;
    struct node* tnode = list->head;
    if (NULL == tnode) {
        printf("the sorted list is empty!\n");
        return;
    }
    struct linkedList* listdst = (struct linkedList*)listDst;
    dlistValueType type = list->type;
    // if 'this' is empty, leave listDst unchanged
    // else free nodes in listDst
    for (int i = 0; i < listdst->size; i++) {
        struct node* temp = listdst->head;
        listdst->head = temp->next;
        free(temp);
    }
    listdst->size = 0;
    // sort
    while(NULL != tnode) {
        struct node* addednode = (struct node*)malloc(sizeof(struct node));
	  addednode->key = tnode->key;
        addednode->value = tnode->value;
        if(dlistIsEmpty(listdst)) {
            addednode->prev = NULL;
            addednode->next = NULL;
            listdst->head = listdst->tail = addednode;
        }
        else {
            struct node* t = listdst->head;
            int flag;
            while(NULL != t) {
                flag = 0;
                switch(method) {
                    case 2: { // inc
                        if (compLarge(addednode, t, type)) {
                            t = t->next;
                            flag = 1;
                        }
                        break;
                    }
                    case 3: { // dec
                        if (compSmall(addednode, t, type)) {
                            t = t->next;
                            flag = 1;
                        }
                        break;
                    }
                }
                if (flag) continue;
                flag = 0;
                // then t > addednode, plug tnode in front of t
                if (NULL == t->prev) {
                    t->prev = addednode;
                    addednode->prev = NULL;
                    addednode->next = t;
                    listdst->head = addednode;
                }
                else {
                    t->prev->next = addednode;
                    addednode->prev = t->prev;
                    addednode->next = t;
                    t->prev = addednode;
                }
                flag = 1;
                break;
            }
            if (flag == 0 || NULL == t) {
                listdst->tail->next = addednode;
                addednode->prev = listdst->tail;
                addednode->next = NULL;
                listdst->tail = addednode;
            }
        }
        listdst->size++;
        tnode = tnode->next;
    }
}

void dlistPrint(dlist_const this) {
    // REQUIRES: argument ' this ' is not null and is a valid list
    // EFFECTS: Print the content of ' this ' in the required format to standard output.
    // A newline must be followed after each line (including the last one).
    struct linkedList* list = (struct linkedList*)this;
    dlistValueType type = list->type;
    if (dlistIsEmpty(list)) {
        printf("The list is empty!\n");
    }
    else {
        struct node* tnode = list->head;
        while(NULL != tnode) {
            printf("%s=", tnode->key);
            switch(type) {
                case 1: // int
                printf("%d\n", tnode->value.intValue);
                break;
                case 2: // string
                printf("%s\n", tnode->value.dlistValue);
                break;
                case 3: // double
                printf("%g\n", tnode->value.doubleValue);
                break;
            }
            tnode = tnode->next;
        }
    }
}

void dlistFree(dlist this) {
    // REQUIRES: argument ' this ' is EITHER NULL or a valid list
    // EFFECTS: if ' this ' is NULL do nothing, other wise frees the list
    // By freeing the list the user also needs to free the data the list manages
    if (NULL == this) return;
    struct linkedList* list = (struct linkedList*)this;
    
    for (int i = 0; i < list->size; i++) {
        if (i == list->size - 1) {
            free(list->head->key);
            free(list->head);
        }
        else {
            list->head = list->head->next;
            free(list->head->prev->key);
            free(list->head->prev);
        }
    }
    free(list);
}

// if node1.value > node2.value, return 1, else return 0
int compLarge(const struct node* node1, const struct node* node2, dlistValueType type) {
    switch(type) {
        case 1: { // int
            int a = node1->value.intValue;
            int b = node2->value.intValue;
            if(a > b) return 1;
            else return 0;
        }
        case 2: { // char*
            char* a = node1->value.dlistValue;
            char* b = node2->value.dlistValue;
            if(strcmp(a, b) > 0) return 1;
            else return 0;
        }
        case 3: { // double
            double a = node1->value.doubleValue;
            double b = node2->value.doubleValue;
            if(a > b) return 1;
            else return 0;
        }
        default: {
            printf("unknown type!\n");
            exit(-1);
        }
    }
}

// if node1.value < node2.value, return 1, else return 0
int compSmall(const struct node* node1, const struct node* node2, dlistValueType type) {
    switch(type) {
        case 1: { // int
            int a = node1->value.intValue;
            int b = node2->value.intValue;
            if(a < b) return 1;
            else return 0;
        }
        case 2: { // char*
            char* a = node1->value.dlistValue;
            char* b = node2->value.dlistValue;
            if(strcmp(a, b) < 0) return 1;
            else return 0;
        }
        case 3: { // double
            double a = node1->value.doubleValue;
            double b = node2->value.doubleValue;
            if(a < b) return 1;
            else return 0;
        }
        default: {
            printf("unknown type!\n");
            exit(-1);
        }
    }
}