/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** main
*/

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include "ftp.h"

static void disconnect_leaving_clients(list_t *list)
{
    client_t *client;
    list_t next;

    if (!(*list))
        return;
    next = (*list)->next;
    for (list_t actual = *list; actual; actual = next) {
        next = actual->next;
        client = GET(client_t, actual);
        if (client->quit)
            client_delete(client, list);
    }
}

static bool run(int socket, char *path, list_t *list)
{
    client_t *client;

    if (accept_new_clients(socket, path, list))
        return false;
    for (list_t cpy = *list; cpy; cpy = cpy->next) {
        client = GET(client_t, cpy);
        client_accept_pasv(client);
        if (client_recv_cmd(client))
            return false;
        if (client->cmd.ended) {
            execute_cmd(client, path);
            client_clear_cmd(client);
        }
    }
    disconnect_leaving_clients(list);
    return true;
}

int main(int ac, char **av)
{
    int socket = -1;
    char *path;
    list_t list = NULL;

    if (ac != 3)
        return 84;
    socket = create_main_socket(atol(av[1]));
    path = realpath(av[2], NULL);
    if (path == NULL || socket == -1)
        return 84;
    while (run(socket, path, &list));
    free(path);
    close(socket);
    return 0;
}
