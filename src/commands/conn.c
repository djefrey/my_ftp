/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** conn
*/

#include <string.h>
#include "ftp.h"

void pasv_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    sockaddr_in_t addr_in;
    char buf[24];

    client_close_data(client);
    if (client_setup_pasv_con(client, &addr_in))
        return;
    sockaddr_to_ip(&addr_in, buf);
    client_send(client, PASV_MODE, buf, strlen(buf));
}

void port_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    sockaddr_in_t addr_in;

    if (is_arg_missing(client, len))
        return;
    client_close_data(client);
    if (ip_to_sockaddr(arg, &addr_in)) {
        client_send(client, INVALID_ARG,
        "Syntax error in parameters or arguments.", 40);
        return;
    }
    addr_in.sin_family = AF_INET;
    client_set_port_addr(client, &addr_in);
    client->conn.mode = PORT;
    client_send(client, COMMAND_OK, "Command ok.", 11);
}

void quit_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    client->quit = true;
    client_send(client, CLOSING_CONTROL_CON,
    "Service closing control connection.", 35);
}
