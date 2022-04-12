/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** client
*/

#include <string.h>
#include "ftp.h"

client_t *client_create(int fd, sockaddr_in_t *addr, list_t *list)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client || list_add(list, client))
        return NULL;
    client->fd = fd;
    client->userid = -1;
    client->username = NULL;
    client->quit = false;
    client->cmd.size = 0;
    client->cmd.free = 0;
    client->cmd.str = NULL;
    client->cmd.ended = false;
    memcpy(&client->addr, addr, sizeof(struct sockaddr_in));
    return client;
}

void client_delete(client_t *client, list_t *list)
{
    if (client->cmd.str)
        free(client->cmd.str);
    close(client->fd);
    list_delete(list, client);
    free(client);
}

void client_clear_cmd(client_t *client)
{
    if (client->cmd.str) {
        free(client->cmd.str);
        client->cmd.str = NULL;
    }
    client->cmd.size = 0;
    client->cmd.free = 0;
    client->cmd.ended = false;
}

bool client_check_logged(client_t *client)
{
    if (client->userid == -1) {
        client_send(client, NOT_LOGGED, "Not logged.");
        return false;
    }
    return true;
}
