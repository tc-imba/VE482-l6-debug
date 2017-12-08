#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab4_dlist.h"

int main(int argc, char* argv[]) {
    char* filename = argv[1];
    FILE* inputFile = fopen(filename, "r");
    char* order = argv[2];
    dlistSortMethod sort;
    if (!strcmp(order, "rand")){
        sort = DLIST_SORT_RAND;
    }
    else if (!strcmp(order, "inc")) {
        sort = DLIST_SORT_INC;
    }
    else if (!strcmp(order, "dec")) {
        sort = DLIST_SORT_DEC;
    }
    char* token;
    token = strtok(filename, "_");
    char* orderGiven = token;
    char* typeGiven = strtok(NULL, ".");
    dlistValueType type;
    if (!strcmp(typeGiven, "int")) {
        type = DLIST_INT;
    }
    else if (!strcmp(typeGiven, "char*")) {
        type = DLIST_STR;
    }
    else if (!strcmp(typeGiven, "double")) {
        type = DLIST_DOUBLE;
    }
    dlist list = createDlist(type);;

    while(!feof(inputFile)) {
        // read information and process
        char tempstr[MAXCHARINLINE];
        fgets(tempstr, MAXLINENUM, inputFile);
        token = strtok(tempstr, "=");
        char* tempkey = (char*)malloc(sizeof(char)*MAXCHARINLINE);

        strcpy(tempkey, token);

        token = strtok(NULL, "=");
        dlistValue value;
        
        switch(type) {
            case 1: // int
            value.intValue = atoi(token);
            break;
            case 2: // string
            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = '\0';
            }
            value.dlistValue = malloc(strlen(token) + 1);
            strcpy(value.dlistValue, token);
            break;
            case 3: // double
            value.doubleValue = atof(token);
            break;
        }
        // add node
        
        dlistAppend(list, tempkey, value);
    }
    dlist dst = createDlist(type);
    dlistSort(list, dst, sort);
    dlistPrint(dst);
    dlistFree(list);
    dlistFree(dst);
    fclose(inputFile);
}