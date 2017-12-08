//
//  dlist.c
//  API
//
//  Created by Cheng on 2017/11/28.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <stdio.h>
#include "dlist.h"
#include "list.h"
dlist createDlist(dlistValueType type)
// EFFECTS: allocate and create a new dlist of datatype 'type' object
//          returns the created dlist object on success
//          returns NULL on error
{
    
    list *newlist = malloc(sizeof(list));
    newlist->first=NULL;
    newlist->type=type;
    newlist->num=0;
    return newlist;
}

int dlistIsEmpty(dlist_const this)
// REQUIRES: argument 'this' is non-null and is a valid list
// EFFECTS: return whether the list 'this' is empty
{
    if(((const list*)this)->num==0 )
        return 1;
    else return 0;
}


void dlistAppend(dlist this,const char* key,dlistValue value)
// REQUIRES: type instantiated in 'value' corresponds to the datatype in the list
// argument 'this' and 'key' are both non-null and valid lists
// EFFECTS : add a line of form ”key=value” to the tail of the dlist
// MODIFIES: modifies 'this'.
{
    addNode(key, value, (list*) this);

}
void dlistSort(dlist_const this,dlist listDst,dlistSortMethod method)// REQUIRES: argument 'this' is not null and is a valid list
// argument 'listDst' is not null and is a valid list
// EFFECTS: Sort 'listSrc' using method given by 'method'.
// Put the results in 'listDst' on success
// Leave 'listDst' unchanged on failure
// * Note 'listDst' may be non-empty when invoked.
// * Be very careful with memory management regarding string lists. // MODIFIES: argument 'listDst'
{
    list* newlist=createDlist(((const list*)this)->type);
    listCopy((const list*)this, newlist);
    
    list* answer=choosingSort(newlist, (list*)listDst, method);
    listCopy(answer, listDst);
    
}
void dlistPrint(dlist_const this)
// REQUIRES: argument 'this' is not null and is a valid list
// EFFECTS: Print the content of 'this' in the required format to standard output.
//          A newline must be followed after each line (including the last one).
{
    list* newlist=createDlist(((const list*)this)->type);
    listCopy((const list*)this, newlist);
    printlist(newlist);
}
void dlistFree(dlist this)
{
    // REQUIRES: argument 'this' is ¡EITHER¿ NULL or a valid list
    // EFFECTS: if 'this' is NULL do nothing, other wise frees the list
    //          By freeing the list the user also needs to free the data
    //          the list manages
        ListFree((list*)this);
}

