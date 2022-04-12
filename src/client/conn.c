/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** conn
*/

#include <string.h>
#include "ftp.h"

static bool add_char_to_cmd(client_t *client, char c)
{
    if (client->cmd.free == 0) {
        client->cmd.str = realloc(client->cmd.str, client->cmd.size + 32);
        if (!(client->cmd.str))
            return true;
        client->cmd.free = 32;
    }
    client->cmd.str[client->cmd.size] = c;
    client->cmd.size += 1;
    client->cmd.free -= 1;
    return false;
}

bool client_recv_cmd(client_t *client)
{
    fd_set rdfds;
    char c;

    FD_ZERO(&rdfds);
    FD_SET(client->fd, &rdfds);
    while (select(client->fd + 1, &rdfds,
    NULL, NULL, &(timeval_t) {0, 100000}) > 0) {
        read(client->fd, &c, 1);
        if (add_char_to_cmd(client, c))
            return true;
        if (client->cmd.size > 2
        && client->cmd.str[client->cmd.size - 2] == '\r'
        && client->cmd.str[client->cmd.size - 1] == '\n') {
            if (add_char_to_cmd(client, '\0'))
                return true;
            client->cmd.ended = true;
            break;
        }
    }
    return false;
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
