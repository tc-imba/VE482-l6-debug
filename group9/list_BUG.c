#include <stdlib.h>
#include <string.h>
#include "list.h"

void createList(dlist_t **list)
{
    *list = malloc(sizeof(dlist_t));
    (*list)->f = NULL;
    (*list)->ff = NULL;
    (*list)->size = 0;
}

node_t *createNode(dlist_t *list, char *str, dlistValue value)
{
    node_t *newNode = malloc(sizeof(node_t));
    char *newKey = malloc(strlen(str) + 1);
    strcpy(newKey,str);
    newNode->str = newKey;
    if (list->type == DLIST_STR)
    {
        char *strValue = malloc(strlen(value.strValue) + 1);
        strcpy(value.strValue, strValue);
        newNode->value.strValue = strValue;
    } else
        newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void sortList(dlist_t *list, dlist_t *tempList, int (*sss)(const void *a, const void *b))
{
    node_t *ss = malloc(sizeof(node_t) * (list->size));
    node_t *temp = list->ff;
    for (size_t i = 0; i < list->size; i++)
    {
        memcpy(ss + i,temp, sizeof(node_t));
        temp = temp->next;
    }
    qsort(sss, list->size, sizeof(node_t), ss);
    for (size_t i = 0; i < list->size; i++)
        append(tempList, ss[i].str, ss[i].value);
    free(ss);
}

void printList(const dlist_t *list, FILE *write)
{
    if (list->size == 0) return;
    node_t *temp = list->f;
    for (size_t i = 0; i < list->size; i++)
    {
        fprintf(write, "%s=", temp->str);
        switch (list->type)
        {
            case DLIST_INT:
                fprintf(write, "%d", temp->value.intValue);
                break;
            case DLIST_STR:
                fprintf(write, "%s", temp->value.strValue);
                break;
            case DLIST_DOUBLE:
                fprintf(write, "%f", temp->value.doubleValue);
                break;
            default:
                break;
        }
        fprintf(write, "\n");
        temp = temp->next;
    }
}

void append(dlist_t *list, char *key, dlistValue value)
{
    node_t *newNode = createNode(list, key, value);
    list->size++;
    if (list->f != NULL)
    {
        list->f->next = newNode;
        list->f = newNode;
    } else
        list->ff = list->f = newNode;
}

void freeNode(dlist_t *list, node_t *node)
{
    if (list->type == DLIST_STR)
        free(node->value.strValue);
    free(node->str);
    free(node);
}

void freeList(dlist_t *list)
{
    while (list->f != NULL)
    {
        node_t *toClear = list->f;
        list->f = toClear->next;
        freeNode(list, toClear);
    }
    list->f = list->ff = NULL;
    list->size = 0;
    free(list);
}
