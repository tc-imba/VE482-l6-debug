#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "list.h"

int stringcmp(const char* lhs, const char* rhs){
    return strcmp(lhs,rhs);
}

int intcmp(const int* lhs, const int* rhs){
    if(*lhs == *rhs) return 0;
    if(*lhs < *rhs) return -1;
    else return 1;
}

int doublecmp(const double* lhs, const double* rhs){
    if(*lhs == *rhs) return 0;
    if(*lhs < *rhs) return -1;
    else return 1;
}

void dll_ctor(dll *list){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void dll_dtor(dll *list){
    node *temp = list->head;
    while(temp){
        free(temp->charptr);
        free(temp->voidptr);
        node *victim = temp;
        temp = temp->next;
        free(victim);
    }
}


void swap(dll *list, node* x, node* y){
    if(x == list->head){
        list->head = y;
    }
    if(y == list->tail){
        list->tail = x;
    }
    x->next = y->next;
    if(y->next){
        y->next->previous = x;
    }
    y->previous = x->previous;
    if(x->previous){
        x->previous->next = y;
    }
    y->next = x;
    x->previous = y;
}

void push_back(dll *list, char *string, void *input){
    node *temp = (node*)malloc(sizeof(node));
    temp->next = NULL;
    temp->previous = NULL;
    temp->charptr = string;
    temp->voidptr = input;

    if(list->head == NULL && list->tail == NULL) {
        list->head = temp;
        list->tail = temp;
        list->size++;
    }
    else {
        list->tail->next = temp;
        temp->previous = list->tail;
        list->tail = temp;
        list->size++;
    }
}

void sort(dll *list, int type, int out_type){
    int (*comparator)(void*,void*);
    switch(type) {
        case (0): {
            comparator = stringcmp;
            break;
        }
        case(1):{
            comparator = intcmp;
            break;
        }
        case(2):{
            comparator = doublecmp;
            break;
        }
        default:{
            fprintf(stderr,"Please select a valid type");
            exit(1);
        }
    }

    node *temp = list->head;
    int swapped = 1;
    int randcount = 0;
    while(swapped){
        swapped = 0;
        temp = list->head;
        while(temp && temp->next){
            switch(out_type){
                case(0):{
                    int x = rand() % 2;
                    if(randcount < 100){
                        if(x){
                           swap(list,temp,temp->next);
                        }
                    }
                    else{
                        return;
                    }
                    swapped = 1;
                    break;
                }
                case(1):{
                    if(comparator(temp->voidptr, temp->next->voidptr) > 0){
                        swap(list, temp, temp->next);
                        swapped = 1;
                    }
                    break;
                }
                case(2):{
                    if(comparator(temp->voidptr, temp->next->voidptr) < 0){
                        swap(list, temp, temp->next);
                        swapped = 1;
                    }
                    break;
                }
                default:{
                    fprintf(stderr,"Wtf invalid type");
                    exit(1);
                }
            }
            temp = temp->next;
        }
    }
}

node *find(dll *list, void *query, int type){
    int (*comparator)(void*,void*);
    switch(type) {
        case (0): {
            comparator = stringcmp;
            break;
        }
        case(1):{
            comparator = intcmp;
            break;
        }
        case(2):{
            comparator = doublecmp;
            break;
        }
        default:{
            fprintf(stderr,"Please select a valid type");
            exit(1);
        }
    }

    node *temp = list->head;
    while(temp!=NULL){
        printf("%lf\n",*((double*)temp->voidptr));
        if(comparator(temp->voidptr,query) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
