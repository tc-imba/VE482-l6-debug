//
//  main.c
//  
//
//  Created by Cheng on 2017/11/28.
//

#include <stdio.h>
#include "dlist.h"

int main() {
    dlist list1 = createDlist(DLIST_INT);
    dlist list2 = createDlist(DLIST_INT);
    dlistValue v1, v2, v3;
    v1.intValue = 1;
    v2.intValue = 2;
    v3.intValue = 3;
    dlistAppend(list1, "c", v3);
    dlistAppend(list1, "a", v1);
    dlistAppend(list1, "b", v2);
    dlistPrint(list1);
    dlistSort(list1, list2, DLIST_SORT_INC);
    dlistPrint(list2);
    dlistFree(list1);
    
    dlistFree(list2);
    return 0;
}
