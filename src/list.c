/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** list
*/

#include <stdlib.h>
#include "list.h"

bool list_add(list_t *root, void *data)
{
    node_t *new = malloc(sizeof(node_t));
    list_t end = *root;

    if (!new)
        return true;
    new->data = data;
    new->next = NULL;
    if (!(*root)) {
        *root = new;
    } else {
        for (; end->next; end = end->next);
        end->next = new;
    }
    return false;
}

void list_delete(list_t *root, void *data)
{
    list_t prev = NULL;
    list_t next = NULL;

    if (!(*root))
        return;
    else if ((*root)->data == data) {
        prev = *root;
        *root = prev->next;
        free(prev);
    } else {
        next = (*root)->next;
        for (list_t actual = *root; actual && actual->data != data;
        prev = actual, actual = next, next = actual->next);
        if (prev->next) {
            free(prev->next);
            prev->next = next;
        }
    }
}
