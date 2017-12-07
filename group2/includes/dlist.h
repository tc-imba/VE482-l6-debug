#include <listdef.h>

#ifndef _LAB4_DLIST_H_
#define _LAB4_DLIST_H_

dlist createDlist(dlistValueType type);
// EFFECTS: allocate and create a new dlist of datatype 'type' object
// returns the created dlist object on success
// returns NULL on error

int dlistIsEmpty(dlist_const this);
// REQUIRES: argument 'this' is non-null and is a valid list
// EFFECTS: return whether the list 'this' is empty

void dlistAppend(dlist this, const char *key, dlistValue value);
// REQUIRES: type instantiated in 'value' corresponds to the datatype in the list
// argument 'this' and 'key' are both non-null and valid lists
// EFFECTS : add a line of form "key=value" to the tail of the dlist
// MODIFIES: modifies 'this'.

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method);
// REQUIRES: argument 'this' is not null and is a valid list
// argument 'listDst' is not null and is a valid list
// EFFECTS: Sort 'listSrc' using method given by 'method'.
// Put the results in 'listDst' on success
// Leave 'listDst' unchanged on failure
// * Note 'listDst' may be non-empty when invoked.
// * Be very careful with memory management regarding string lists.
// MODIFIES: argument 'listDst'

void dlistPrint(dlist_const this);
// REQUIRES: argument 'this' is not null and is a valid list
// EFFECTS: Print the content of 'this' in the required format to standard output.
// A newline must be followed after each line (including the last one).

void dlistFree(dlist this);
// REQUIRES: argument 'this' is <EITHER> NULL or a valid list
// EFFECTS: if 'this' is NULL do nothing, other wise frees the list
// By freeing the list the user also needs to free the data
// the list manages

#endif

#ifndef __FILE_HANDLER__
#define __FILE_HANDLER__

void file_write(char *outfile, dlist this);
void file_read(char *argv[], char *token, dlist this);
#endif