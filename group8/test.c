//
//  test.c
//  
//
//  Created by Horizon on 28/11/2017.
//
#define err1 DLIST_RANDOM
#include <stdio.h>
#include "lab4_dlist.h"
int main(){
    dlist dlist2=createDlist(DLIST_DOUBLE);
    dlist dlist3=createDlist(DLIST_STR);
    printf("Create fail? 2:%d 3:%d\n",dlist2==NULL,dlist3==NULL);
    dlistValue t2;
    dlistValue t3;
    t2.doubleValue=1.00;
    dlistAppend(dlist2, "1",t2);
    t2.doubleValue=1.01;
    dlistAppend(dlist2, "2",t2);
    t2.doubleValue=0.99;
    dlistAppend(dlist2, "3",t2);
    t2.doubleValue=2;
    dlistAppend(dlist2, "4",t2);
    t3.strValue="a";
    dlistAppend(dlist3, "1",t3);
    t3.strValue="dccdcdcdcdqswswswsws";
    dlistAppend(dlist3, "2",t3);
    t3.strValue="ac";
    dlistAppend(dlist3, "3",t3);
    t3.strValue="b";
    dlistAppend(dlist3, "4",t3);
    dlistSort(dlist2, dlist2, DLIST_SORT_DEC);
    dlistPrint(dlist2);
    dlistFree(dlist2);
    dlistSort(dlist3, dlist3, DLIST_SORT_INC);
    dlistPrint(dlist3);
    dlistFree(dlist3);
}
