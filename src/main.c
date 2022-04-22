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

static bool wait_until_recv(int socket,
list_t list, fd_set *rdset, fd_set *wrset)
{
    client_t *client;
    int biggest = socket;

    FD_ZERO(rdset);
    FD_ZERO(wrset);
    FD_SET(socket, rdset);
    for (; list; list = list->next) {
        client = GET(client_t, list);
        FD_SET(client->conn.control, rdset);
        FD_SET(client->conn.control, wrset);
        if (client->conn.control > biggest)
            biggest = client->conn.control;
        if (client->conn.listening_socket != -1) {
            FD_SET(client->conn.listening_socket, rdset);
            biggest = client->conn.listening_socket > biggest
            ? client->conn.listening_socket : biggest;
        }
    }
    return select(biggest + 1, rdset, wrset, NULL, NULL) == -1;
}

static bool client_update(client_t *client,
char *path, fd_set *rdset, fd_set *wrset)
{
    int ctrl = client->conn.control;

    if (client->conn.listening_socket != -1
    && FD_ISSET(client->conn.listening_socket, rdset))
        client_accept_pasv(client);
    if (!(FD_ISSET(ctrl, rdset) && FD_ISSET(ctrl, wrset)))
        return false;
    if (client_recv_cmd(client))
        execute_cmd(client, path);
    return false;
}

static bool run(int socket, char *path, list_t *list)
{
    client_t *client;
    fd_set rdset;
    fd_set wrset;

    if (wait_until_recv(socket, *list, &rdset, &wrset))
        return false;
    if (FD_ISSET(socket, &rdset) && accept_new_clients(socket, path, list))
        return false;
    for (list_t cpy = *list; cpy; cpy = cpy->next) {
        client = GET(client_t, cpy);
        if (client_update(client, path, &rdset, &wrset))
            return false;
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
