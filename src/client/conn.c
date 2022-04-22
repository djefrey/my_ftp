/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** conn
*/

#include <string.h>
#include "ftp.h"

static bool client_get_cmd_from_buffer(client_t *client, char buf[1024], uint size)
{
    uint i = 0;

    for (; i < size; i++, client->cmd.size++) {
        if (client->cmd.size == 1024) {
            memset(client->cmd.cmd, 0, 1024);
            client->cmd.size = 0;
            client_send(client, INVALID_CMD, "Command too long.", 17);
            return false;
        }
        client->cmd.cmd[client->cmd.size] = buf[i];
        if (client->cmd.size > 1
        && !strncmp(client->cmd.cmd + client->cmd.size - 1, CRLF, 2))
            return true;
    }
    return false;
}

bool client_recv_cmd(client_t *client)
{
    char buf[1024];
    uint size = read(client->conn.control, buf, 1024);

    if (size == 0) {
        client->quit = true;
        return false;
    } else if (size == 1024) {
        client_send(client, INVALID_CMD, "Command too long.", 17);
        return false;
    }
    return client_get_cmd_from_buffer(client, buf, size);
}

bool client_send(client_t *client, int code, char *msg, size_t len)
{
    char buf[4 + len + 2 + 1];
    size_t size = 5;

    snprintf(buf, 4, "%03i", code);
    if (len > 0) {
        buf[3] = ' ';
        memcpy(buf + 4, msg, len);
        size += 1 + len;
    }
    memcpy(len ? buf + 4 + len : buf + 3, CRLF, 3);
    write(client->conn.control, buf, size);
    return false;
}

void client_accept_pasv(client_t *client)
{
    socklen_t addr_size = sizeof(struct sockaddr);
    struct sockaddr_in addr_in;

    if (client->conn.mode != PASV || client->conn.data != -1)
        return;
    client->conn.data = accept(client->conn.listening_socket,
    (sockaddr_t*) &addr_in, &addr_size);
}
