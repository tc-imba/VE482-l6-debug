#include <stdio.h>
#include "list.h"
#include "lab4_dlist.h"

int main()
{
    dlist_t *listInt=createDlist(DLIST_INT);
    dlistValue v1;
    v1.intValue=1;
    dlistAppend(listInt,"a",v1);
    dlistValue v3;
    v3.intValue=3;
    dlistAppend(listInt,"c",v3);
    dlistValue v2;
    v2.intValue=2;
    dlistAppend(listInt,"b",v2);
    dlistValue v0;
    v0.intValue=0;
    dlistAppend(listInt,"d",v0);
    dlist_t *sortListInt=createDlist(DLIST_INT);
    dlistSort(listInt,sortListInt,DLIST_SORT_INC);
    dlistPrint(listInt);
    printf("\n");
    dlistPrint(sortListInt);

    printf("\n");

    dlist_t *listDouble=createDlist(DLIST_DOUBLE);
    dlistValue d1;
    d1.doubleValue=-1.05;
    dlistAppend(listDouble,"a",d1);
    dlistValue d3;
    d3.doubleValue=3.03;
    dlistAppend(listDouble,"c",d3);
    dlistValue d2;
    d2.doubleValue=2.30009;
    dlistAppend(listDouble,"b",d2);
    dlistValue d0;
    d0.doubleValue=-100.324;
    dlistAppend(listDouble,"d",d0);
    dlist_t *sortListDouble=createDlist(DLIST_DOUBLE);
    dlistSort(listDouble,sortListDouble,DLIST_SORT_DEC);
    dlistPrint(listDouble);
    printf("\n");
    dlistPrint(sortListDouble);

    printf("\n");

    dlist_t *listString=createDlist(DLIST_STR);
    dlistValue s1;
    s1.strValue="bcup";
    dlistAppend(listString,"a",s1);
    dlistValue s3;
    s3.strValue="zcup";
    dlistAppend(listString,"c",s3);
    dlistValue s2;
    s2.strValue="ccup";
    dlistAppend(listString,"b",s2);
    dlistValue s0;
    s0.strValue="acup";
    dlistAppend(listString,"d",s0);
    dlist_t *sortListString=createDlist(DLIST_STR);
    dlistSort(listString,sortListString,DLIST_SORT_INC);
    dlistPrint(listString);
    printf("\n");
    dlistPrint(sortListString);

    dlistFree(listInt);
    dlistFree(sortListInt);
    dlistFree(listDouble);
    dlistFree(sortListDouble);
    dlistFree(listString);
    dlistFree(sortListString);
    return 0;
}