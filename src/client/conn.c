/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** conn
*/

#include <string.h>
#include "ftp.h"

static bool add_char_to_str(char c, char **str, int *size, int *free)
{
    if (*free == 0) {
        *str = realloc(*str, *size + 32);
        if (!(*str))
            return true;
        *free = 32;
    }
    (*str)[*size] = c;
    *size += 1;
    *free -= 1;
    return false;
}

char *client_recv(client_t *client)
{
    fd_set rdfds;
    char *str = NULL;
    int size = 0;
    int free = 0;
    char c;

    FD_ZERO(&rdfds);
    FD_SET(client->fd, &rdfds);
    while (select(client->fd + 1, &rdfds,
    NULL, NULL, &(timeval_t) {0, 100000}) > 0) {
        read(client->fd, &c, 1);
        if (add_char_to_str(c, &str, &size, &free))
            return NULL;
        if (size > 2 && str[size - 2] == '\r' && str[size - 1] == '\n')
            break;
    }
    if (str && add_char_to_str('\0', &str, &size, &free))
        return NULL;
    return str;
}

bool client_send(client_t *client, int code, char *msg)
{
    fd_set wrfds;

    FD_ZERO(&wrfds);
    FD_SET(client->fd, &wrfds);
    if (select(client->fd + 1, NULL, &wrfds, NULL, &(timeval_t) {0, 10}) <= 0)
        return true;
    dprintf(client->fd, "%03i %s%s", code, msg, CRLF);
    return false;
}
