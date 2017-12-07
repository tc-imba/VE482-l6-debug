#ifndef __LIST_HEADER__
#define __LIST_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#endif

#ifndef _DEF_DLIST_H_
#define _DEF_DLIST_H_

// Data type stored in the dlist
typedef enum dlistValueType_t {
    DLIST_INT = 0x01,    // list contains int values
    DLIST_STR = 0x02,    // list contains char* values
    DLIST_DOUBLE = 0x03, // list contains double values
    DLIST_UNKOWN = 0x00
} dlistValueType;

// Different options for sorting
// String are sorted in lexical order
typedef enum dlistSortMethod_t {
    DLIST_SORT_RAND = 0x01, // Randomize entries
    DLIST_SORT_INC = 0x02,  // Sort in ascending order
    DLIST_SORT_DEC = 0x03,  // Sort in descending order
    DLIST_SORT_UNKOWN = 0x00
} dlistSortMethod;

// The value stored in the dlist
// Research online what an "union" is.
typedef union dlistValue_t {
    int intValue;
    double doubleValue;
    char *strValue;
} dlistValue;

typedef void *dlist;
typedef const void *dlist_const;

#endif

#ifndef __LIST_TYPE__
#define __LIST_TYPE__

typedef struct n
{
    struct n *next;
    char *op;
    dlistValue value;
} node;

typedef struct linked_list
{
    node *first;
    node *last;
    dlistValueType type;
} vector; // The pointer to the first node (NULL if none)
#define LSH_TOK_BUFSIZE 10
#endif

#ifndef __LIST_FUNC__
#define __LIST_FUNC__

int compare(const dlistValue x1, const dlistValue x2, const dlistValueType type, const dlistSortMethod method);
//int inc(const void *x1, const void *x2, const dlistValueType type);
//int dec(const void *x1, const void *x2, const dlistValueType type);
//int rnd(const void *x1, const void *x2, const dlistValueType type);
//node *search(char *key);
//void del(char *key);
//void file_format(char *argv[], char *outfile, char *infile, char *token);
//void file_format(char *argv[], char *outfile, char *infile);
void BubbleSort(dlist this, dlistSortMethod method);
#define CAST(ptr, type) (((type)ptr))
#endif