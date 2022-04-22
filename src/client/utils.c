/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** utils
*/

#include <string.h>
#include "ftp.h"

bool client_check_logged(client_t *client)
{
    if (client->userid == -1) {
        client_send(client, NOT_LOGGED, "Not logged in.", 14);
        return false;
    }
    return true;
}

void client_set_port_addr(client_t *client, sockaddr_in_t *sockaddr)
{
    memcpy(&client->conn.port_addr, sockaddr, sizeof(sockaddr_in_t));
}

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

bool client_setup_pasv_con(client_t *client, sockaddr_in_t *addr_in)
{
    int fd = open_data_socket(client);
    socklen_t socklen = sizeof(sockaddr_in_t);

    if (fd == -1) {
        client_send(client, DATA_NOT_OPEN, "Can't open data connection.", 27);
        return true;
    }
    if (getsockname(fd, (sockaddr_t*) addr_in, &socklen) == -1) {
        client_send(client, DATA_NOT_OPEN, "Can't open data connection.", 27);
        return true;
    }
    client = client;
    if (listen(fd, 1) == -1) {
        client_send(client, DATA_NOT_OPEN, "Can't open data connection.", 27);
        return true;
    }
    client->conn.mode = PASV;
    client->conn.listening_socket = fd;
    return false;
}

bool client_connect_to_data(client_t *cl)
{
    sockaddr_in_t *addr_in = &cl->conn.port_addr;
    int fd;

    client_send(cl, FILE_STATUS_OK,
    "File status okay; about to open data connection.", 48);
    if (cl->conn.mode == NONE
    || (cl->conn.mode == PASV && cl->conn.data == -1)) {
        client_send(cl, DATA_NOT_OPEN, "Can't open data connection.", 27);
        return true;
    }
    if (cl->conn.mode == PORT) {
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(fd, (sockaddr_t*) addr_in, sizeof(sockaddr_in_t)) == -1) {
            client_send(cl, DATA_NOT_OPEN, "Can't open data connection.", 27);
            close(fd);
            return true;
        }
        cl->conn.data = fd;
    }
    return false;
}
