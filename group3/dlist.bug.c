//
// Created by liu on 17-11-23.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dlist.h"

typedef struct node {
    char *str;
    dlistValue data;
    size_t pn;
} node_t;

typedef struct list {
    struct node *zero, *first, *last;
    size_t length;
    dlistValueType type;
} list_t;

typedef struct list_iter {
    const struct list* list;
    struct node *a, *b;
} list_iter_t;

static void list_iter_next(list_iter_t *it) {
    node_t *next;
    if (it->b == it->list->last) {
        next = it->list->zero;
    } else {
        next = (node_t *) (it->b->pn ^ (size_t) it->a);
    }
    it->a = it->b;
    it->b = next;
}

static void list_iter_init(const list_t *list, list_iter_t *it) {
    it->list = list;
    it->a = list->zero;
    it->b = list->first;
}

static int list_iter_end(list_iter_t *it) {
    return it->a == it->list->zero || it->list->length == 0;
}

static node_t *list_iter_get(list_iter_t *it) {
    return it->b;
}

static node_t *list_node_init(list_t *list, const char *str, dlistValue data) {
    node_t *new_node = malloc(sizeof(node_t));
    char *key = malloc(strlen(str) + 1);
    strcpy(key, str);
    new_node->str = key;
    if (list->type == DLIST_STR) {
        char *str_data = malloc(strlen(data.strValue) + 1);
        strcpy(str_data, data.strValue);
        new_node->data.strValue = str_data;
    } else {
        new_node->data = data;
    }
    return new_node;
}

static void list_node_free(list_t *list, node_t *node) {
    if (list->type == DLIST_STR) {
        free(node->data.strValue);
    }
    free(node->str);
    free(node);
}

static void list_init(list_t **list) {
    *list = malloc(sizeof(list_t));
    node_t *temp = malloc(sizeof(node_t));
    temp->str = NULL;
    temp->pn = 0;
    (*list)->zero = temp;
    (*list)->first = NULL;
    (*list)->last = NULL;
    (*list)->length = 0;
}

static void list_clear(list_t *list) {
    list_iter_t it;
    node_t *temp = NULL;
    for (list_iter_init(list, &it); !list_iter_end(&it); list_iter_next(&it)) {
        if (temp) list_node_free(list, temp);
        temp = list_iter_get(&it);
    }
    if (temp) list_node_free(list, temp);
    list->first = list->last = NULL;
    list->length = 0;
}

static void list_free(list_t *list) {
    list_clear(list);
    free(list->zero);
    free(list);
}

static node_t *list_append(list_t *list, const char *str, dlistValue data) {
    node_t *new_node = list_node_init(list, str, data);
    list->length++;
    if (list->last) {
        new_node->pn = (size_t) list->last;
        list->last->pn = (size_t) new_node;
    } else {
        new_node->pn = 0;
        list->first = new_node;
    }
    list->last = new_node;
    return new_node;
}

static void list_sort(const list_t *list, list_t *new_list, int (*cmp)(const void *, const void *)) {
    node_t *arr = malloc(sizeof(node_t) * list->length);
    list_iter_t it;
    int i = 0;
    for (list_iter_init(list, &it); !list_iter_end(&it); list_iter_next(&it)) {
        memcpy(arr + (i++), list_iter_get(&it), sizeof(node_t));
    }
    qsort(arr, list->length, sizeof(node_t), cmp);
    for (i = 0; i < list->length; ++i) {
        list_append(new_list, arr[i].str, arr[i].data);
    }
    free(arr);
}

static void list_print(const list_t *list, FILE *file) {
    list_iter_t it;
    for (list_iter_init(list, &it); !list_iter_end(&it); list_iter_next(&it)) {
        node_t *temp = list_iter_get(&it);
        fprintf(file, "%s=", temp->str);
        switch (list->type) {
        case DLIST_STR:
            fprintf(file, "%s\n", temp->data.strValue);
            break;
        case DLIST_INT:
            fprintf(file, "%d\n", temp->data.intValue);
            break;
        case DLIST_DOUBLE:
            fprintf(file, "%lf", temp->data.doubleValue);
            break;
        default:
            assert(0);
        }
    }
}

static int int_inc(const void *a, const void *b) {
    int _a = ((node_t *) a)->data.intValue;
    int _b = ((node_t *) b)->data.intValue;
    if (_a > _b) return 1;
    if (_a < _b) return -1;
    return 0;
}

static int int_dec(const void *a, const void *b) {
    return int_inc(b, a);
}

static int double_inc(const void *a, const void *b) {
    double _a = ((node_t *) a)->data.doubleValue;
    double _b = ((node_t *) b)->data.doubleValue;
    if (_a > _b) return 1;
    if (_a < _b) return -1;
    return 0;
}

static int double_dec(const void *a, const void *b) {
    return double_inc(b, a);
}

static int string_inc(const void *a, const void *b) {
    return strcmp(((node_t *) a)->data.strValue, ((node_t *) b)->data.strValue);
}

static int string_dec(const void *a, const void *b) {
    return strcmp(((node_t *) b)->data.strValue, ((node_t *) a)->data.strValue);
}

static int all_rand(const void *a, const void *b) {
    return (rand() % 2) * 2 - 1;
}

static int (*const cmp[3][3])(const void *, const void *) = {
        {all_rand, int_inc,    int_dec},
        {all_rand, string_inc, string_dec},
        {all_rand, double_inc, double_dec},
};

dlist createDlist(dlistValueType type) {
    if (type > DLIST_UNKOWN && type <= DLIST_DOUBLE) {
        list_t *list;
        list_init(&list);
        list->type = type;
        return list;
    }
    return NULL;
}

int dlistIsEmpty(dlist_const this) {
    return ((const list_t *) this)->length == 0;
}

void dlistAppend(dlist this, const char *key, dlistValue value) {
    list_append(this, key, value);
}

void dlistSort(dlist_const this, dlist listDst, dlistSortMethod method) {
    list_clear(listDst);
    dlistValueType type = ((const list_t *) (this))->type;
    if (type <= DLIST_UNKOWN || type > DLIST_DOUBLE) {
        return;
    }
    if (method <= DLIST_SORT_UNKOWN || method > DLIST_SORT_DEC) {
        return;
    }
    list_sort(this, listDst, cmp[type - 1][method - 1]);
}

void dlistPrint(dlist_const this) {
    list_print(this, stdout);
}

void dlistFree(dlist this) {
    list_free(this);
}
