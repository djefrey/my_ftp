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
    FD_SET(client->conn.control, &rdfds);
    while (!client->quit && select(client->conn.control + 1, &rdfds,
    NULL, NULL, &(timeval_t) {0, 10}) > 0) {
        if (read(client->conn.control, &c, 1) == 0)
            client->quit = true;
        if (add_char_to_cmd(client, c))
            return true;
        if (client->cmd.size > 2
        && !strncmp(client->cmd.str + client->cmd.size - 2, CRLF, 2)) {
            if (add_char_to_cmd(client, '\0'))
                return true;
            client->cmd.ended = true;
            break;
        }
    }
    return false;
}

bool client_send(client_t *client, int code, char *msg, size_t len)
{
    char buf[4 + len + 2 + 1];
    size_t size = 5;
    fd_set wrfds;

    snprintf(buf, 4, "%03i", code);
    if (len > 0) {
        buf[3] = ' ';
        memcpy(buf + 4, msg, len);
        size += 1 + len;
    }
    memcpy(len ? buf + 4 + len : buf + 3, CRLF, 3);
    FD_ZERO(&wrfds);
    FD_SET(client->conn.control, &wrfds);
    if (select(client->conn.control + 1, NULL,
    &wrfds, NULL, &(timeval_t) {0, 10}) <= 0)
        return true;
    write(client->conn.control, buf, size);
    return false;
}

void client_accept_pasv(client_t *client)
{
    socklen_t addr_size = sizeof(struct sockaddr);
    struct sockaddr_in addr_in;
    fd_set rdset;

    if (client->conn.mode != PASV || client->conn.data != -1)
        return;
    FD_ZERO(&rdset);
    FD_SET(client->conn.listening_socket, &rdset);
    if (select(client->conn.listening_socket + 1, &rdset,
    NULL, NULL, &(struct timeval) {0, 10}) <= 0)
        return;
    client->conn.data = accept(client->conn.listening_socket,
    (sockaddr_t*) &addr_in, &addr_size);
}
