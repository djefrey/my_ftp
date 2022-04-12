/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** list
*/

#pragma once

#include <stdbool.h>

typedef struct node_s {
    void *data;
    struct node_s *next;
} node_t;
typedef node_t *list_t;

#define GET(type, list) ((type*) (list->data))

bool list_add(list_t *root, void *data);
void list_delete(list_t *root, void *data);
