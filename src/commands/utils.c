/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** utils
*/

#include "ftp.h"

bool is_arg_missing(client_t *client, size_t len)
{
    if (len == 0) {
        client_send(client, INVALID_ARG,
        "Syntax error in parameters or arguments.", 40);
        return true;
    }
    return false;
}

bool check_alloc(client_t *client, void *ptr)
{
    if (ptr == NULL) {
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
        return true;
    }
    return false;
}
