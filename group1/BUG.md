# Definite bugs

## main.c line 49
```
tempkey = token;
```
change to
```
strcpy(tempkey, token);
```

## main.c line 53
```
value.dlistValue = token;
```
change to
```
if (token[strlen(token) - 1] == '\n') {
    token[strlen(token) - 1] = '\0';
}
value.dlistValue = malloc(strlen(token) + 1);
strcpy(value.dlistValue, token);
```
or add similar malloc in dlistAppend (I added it here because the origin code malloc the key in main.c, but actually the two mallocs should all be in lab4_dlist.c)

# Logical bugs

## lab4_dlist.c line 95-96
```
addednode->key = tnode->key;
addednode->value = tnode->value;
```
change to
```
addednode->key = malloc(strlen(tnode->key) + 1);
strcpy(addednode->key, tnode->key);
if (list->type == DLIST_STR) {
    addednode->value.dlistValue = malloc(strlen(tnode->value.dlistValue) + 1);
    strcpy(addednode->value.dlistValue, tnode->value.dlistValue);
}
```

## lab4_dlist.c line 190-198
```
if (i == list->size - 1) {
    free(list->head->key);
    free(list->head);
}
else {
    list->head = list->head->next;
    free(list->head->prev->key);
    free(list->head->prev);
}
```
change to
```
if (i == list->size - 1) {
    free(list->head->key);
    if (list->type == DLIST_STR) {
        free(list->head->value.dlistValue);
    }
    free(list->head);
} else {
    list->head = list->head->next;
    free(list->head->prev->key);
    if (list->type == DLIST_STR) {
        free(list->head->prev->value.dlistValue);
    }
    free(list->head->prev);
}
```