#include "listdef.h"

void BubbleSort(dlist this, dlistSortMethod method)
{
    node *head = CAST(this, vector *)->first;
    node *tail = CAST(this, vector *)->last;
    dlistValueType type = CAST(this, vector *)->type;
    dlistValue tmp_value;
    char tmp_op[100];
    while (tail != head)
    {
        for (node *p = head; p->next != NULL; p = p->next)
        {
            if (compare(p->value, head->value, type, method) < 0)
            {
                tmp_value = p->value;
                p->value = head->value;
                head->value = tmp_value;
                strcpy(tmp_op, p->op);
                strcpy(p->op, head->op);
                strcpy(head->op, tmp_op);
            }
        }
        head = head->next;
    }
}