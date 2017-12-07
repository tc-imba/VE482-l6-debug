#include "listdef.h"

int compare(const dlistValue x1, const dlistValue x2, const dlistValueType type, const dlistSortMethod method)
{
    int ans = 0;
    switch (type)
    {
    case DLIST_STR:
        ans = strcmp(x1.strValue, x2.strValue);
        break;
    case DLIST_INT:
        ans = x1.intValue - x2.intValue;
        break;
    case DLIST_DOUBLE:
        ans = (int)(x1.doubleValue - x2.doubleValue);
        break;
    default:
        break;
    }
    //printf("x1: %d, x2: %d, ans: %d\n", x1.intValue, x2.intValue, ans);
    switch (method)
    {
    case DLIST_SORT_UNKOWN:
        ans = 0;
        break;
    case DLIST_SORT_DEC:
        ans = -ans;
        break;
    case DLIST_SORT_RAND:
        ans = (rand() % 3) - 1;
        break;
    default:
        break;
    }
    return ans;
}