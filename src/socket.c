/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** socket
*/

#include <string.h>
#include "ftp.h"

int create_main_socket(short port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr_in;

    if (fd == -1)
        return -1;
    addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_in.sin_port = htons(port);
    addr_in.sin_family = AF_INET;
    if (bind(fd, (sockaddr_t*) &addr_in, sizeof(addr_in)))
        return -1;
    if (listen(fd, 1))
        return -1;
    return fd;
}

void accept_new_clients(int socket, list_t *list)
{
    socklen_t addr_size = sizeof(struct sockaddr);
    struct sockaddr_in addr_in;
    fd_set rdfds;
    int fd;
    client_t *client;

    FD_ZERO(&rdfds);
    FD_SET(socket, &rdfds);
    while (select(socket + 1, &rdfds, 0, 0, &(timeval_t) {0, 10}) > 0) {
        fd = accept(socket, (sockaddr_t*) &addr_in, &addr_size);
        if (fd == -1)
            continue;
        client = client_create(fd, &addr_in, list);
        if (!client)
            continue;
        client_send(client, RDY_FOR_NEW_USER, "");
    }
}
