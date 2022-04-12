/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** ftp
*/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "responses.h"
#include "list.h"

#define CRLF "\r\n"
#define ANONYMOUS_USERID 0

typedef unsigned int uint;
typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct timeval timeval_t;

typedef struct cmd_s {
    uint size;
    uint free;
    char *str;
    bool ended;
} cmd_t;

typedef struct client_s {
    int fd;
    int userid;
    char *username;
    bool quit;
    struct sockaddr_in addr;
    cmd_t cmd;
} client_t;

int dprintf(int fd, const char *restrict format, ...);

int create_main_socket(short port);
bool accept_new_clients(int socket, list_t *list);

client_t *client_create(int fd, sockaddr_in_t *addr, list_t *list);
void client_delete(client_t *client, list_t *list);
void client_clear_cmd(client_t *client);
bool client_check_logged(client_t *client);

bool client_recv_cmd(client_t *client);
bool client_send(client_t *client, int code, char *msg);

bool execute_cmd(client_t *client);
