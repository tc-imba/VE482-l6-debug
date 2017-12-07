#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void readfile(dlist lists, char *filename);
void sort(dlist list, dlist listDst, char *type);
dlistValueType det_type(char *filename);