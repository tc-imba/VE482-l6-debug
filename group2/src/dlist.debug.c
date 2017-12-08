#include "dlist.h"

dlist createDlist(dlistValueType type)
{
	dlist tmp = malloc(sizeof(vector));
	CAST(tmp, vector *)->type = type;
	CAST(tmp, vector *)->first = NULL;
	CAST(tmp, vector *)->last = NULL;
	return tmp;
}

int dlistIsEmpty(dlist_const this)
{
	if (CAST(this, vector *)->first == NULL)
		return 1;
	return 0;
}

void dlistAppend(dlist this, const char *key, dlistValue value)
{
	node *new = (node *)malloc(sizeof(node));
	new->op = (char *)malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(new->op, key);
	new->value = value;
	//printf("key: %s; value: %d\n", key, value.intValue);
	if (dlistIsEmpty(this))
	{
		CAST(this, vector *)->first = CAST(this, vector *)->last = new;
		new->next = NULL;
		return;
	}
	CAST(this, vector *)->last->next = new;
	CAST(this, vector *)->last = new;
	new->next = NULL;
	return;
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method)
{
	printf("Sorting elements\n");
	if (CAST(listDst, vector *)->first != NULL)
		return;
	for (node *p = CAST(this, vector *)->first; p != NULL; p = p->next)
    {
        dlistValue value = p->value;
        if (CAST(this, vector *)->type == DLIST_STR)
        {
            value.strValue = malloc(strlen(p->value.strValue) + 1);
            strcpy(value.strValue, p->value.strValue);
        }
        dlistAppend(listDst, p->op, value);
    }
	BubbleSort(listDst, method);
}

void dlistPrint(dlist_const this)
{
	node *p;
	for (p = CAST(this, vector *)->first; p != NULL; p = p->next)
	{
		switch (CAST(this, vector *)->type)
		{
		case DLIST_STR:
			printf("%s=%s\n", p->op, p->value.strValue);
			break;
		case DLIST_INT:
			printf("%s=%d\n", p->op, p->value.intValue);
			break;
		case DLIST_DOUBLE:
			printf("%s=%lf\n", p->op, p->value.doubleValue);
			break;
		default:
			printf("\n");
		}
	}
}

void dlistFree(dlist this)
{
	node *p, *victim;
	for (p = CAST(this, vector *)->first; p != NULL;)
	{
		victim = p;
		p = p->next;
		free(victim->op);
        if (CAST(this, vector *)->type == DLIST_STR)
            free(victim->value.strValue);
		free(victim);
	}
	free(this);
}
