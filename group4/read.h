#ifndef READ_H
#define READ_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

enum dlistValueType_t gettype(char * filename);
enum dlistSortMethod_t getorder(char* ordername);
void getfile(list* dlist, FILE* file);
void fileprint(list* dlist,FILE* fp);

#endif
