/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** client
*/

#include <string.h>
#include "ftp.h"

client_t *client_create(int fd, sockaddr_in_t *addr, char *path, list_t *list)
{
    client_t *client = malloc(sizeof(client_t));
    char *cwd = strdup(path);

    if (!client || !cwd || list_add(list, client))
        return NULL;
    client->conn.control = fd;
    client->conn.data = -1;
    client->conn.listening_socket = -1;
    client->conn.mode = NONE;
    client->userid = -1;
    client->username = NULL;
    client->quit = false;
    client->cwd = cwd;
    client->cmd.size = 0;
    client->cmd.free = 0;
    client->cmd.str = NULL;
    client->cmd.ended = false;
    memcpy(&client->addr, addr, sizeof(sockaddr_in_t));
    return client;
}

void client_delete(client_t *client, list_t *list)
{
    if (client->cmd.str)
        free(client->cmd.str);
    client_close_data(client);
    close(client->conn.control);
    list_delete(list, client);
    free(client);
}

void client_close_data(client_t *client)
{
    if (client->conn.data != -1)
        close(client->conn.data);
    if (client->conn.listening_socket != -1)
        close(client->conn.listening_socket);
    client->conn.data = -1;
    client->conn.listening_socket = -1;
    client->conn.mode = NONE;
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
