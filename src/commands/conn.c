/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** conn
*/

#include <string.h>
#include "ftp.h"

static int open_data_socket(client_t *client)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in_t addr_in;

    if (fd == -1)
        return -1;
    addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_in.sin_port = 0;
    addr_in.sin_family = AF_INET;
    if (bind(fd, (sockaddr_t*) &addr_in, sizeof(addr_in)))
        return -1;
    if (listen(fd, 1))
        return -1;
    return fd;
}

void pasv_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    int fd = open_data_socket(client);
    sockaddr_in_t addr_in;
    socklen_t socklen = sizeof(addr_in);
    char buf[24];

    client_close_data(client);
    if (fd == -1) {

        return;
    }
    if (getsockname(fd, (sockaddr_t*) &addr_in, &socklen) == -1) {

        return;
    }
    if (listen(fd, 1) == -1) {

        return;
    }
    client->conn.mode = PASV;
    client->conn.listening_socket = fd;
    sockaddr_to_ip(&addr_in, buf);
    client_send(client, PASV_MODE, buf, strlen(buf));
}

void port_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    int fd;
    sockaddr_in_t addr_in;

    if (is_arg_missing(client, len))
        return;
    client_close_data(client);
    if (ip_to_sockaddr(arg, &addr_in)) {
        client_send(client, INVALID_ARG,
        "Syntax error in parameters or arguments.", 40);
        return;
    }
    fd = socket(AF_INET, SOCK_STREAM, 0);
    addr_in.sin_family = AF_INET;
    if (connect(fd, (sockaddr_t*) &addr_in, sizeof(sockaddr_in_t)) == -1) {
        client_send(client, INVALID_ARG, "Errr.", 5);
        close(fd);
        return;
    }
    client->conn.mode = PORT;
    client->conn.data = fd;
    client_send(client, COMMAND_OK, "Command ok.", 11);
}

void quit_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    client->quit = true;
    client_send(client, CLOSING_CONTROL_CON,
    "Service closing control connection.", 35);
}
