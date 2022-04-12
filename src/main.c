/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** main
*/

#include <errno.h>
#include <string.h>
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

static bool run(int socket, list_t *list)
{
    client_t *client;

    if (accept_new_clients(socket, list))
        return false;
    for (list_t cpy = *list; cpy; cpy = cpy->next) {
        client = GET(client_t, cpy);
        if (client_recv_cmd(client))
            return false;
        if (client->cmd.ended) {
            execute_cmd(client);
            client_clear_cmd(client);
        }
    }
    disconnect_leaving_clients(list);
    return true;
}

int main(int ac, char **av)
{
    int socket = create_main_socket(atol(av[1]));
    list_t list = NULL;

    if (socket == -1)
        return 84;
    while (run(socket, &list));
    return 0;
}
