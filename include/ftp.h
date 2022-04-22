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
#define LOCAL_ERROR_SEND(client) \
    client_send(client, LOCAL_ERROR,  \
    "Requested action aborted. Local error in processing.", 52);

typedef unsigned int uint;
typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct timeval timeval_t;

typedef enum con_mode_e {
    NONE,
    PASV,
    PORT,
} con_mode_t;

typedef struct cmd_s {
    char cmd[1024];
    uint size;
} cmd_t;

typedef struct connection_s {
    int control;
    int data;
    int listening_socket;
    sockaddr_in_t port_addr;
    con_mode_t mode;
} connection_t;

typedef struct client_s {
    connection_t conn;
    int userid;
    char *username;
    char *cwd;
    bool quit;
    struct sockaddr_in addr;
    cmd_t cmd;
} client_t;

int dprintf(int fd, const char *restrict format, ...);

int create_main_socket(short port);
bool accept_new_clients(int socket, char *path, list_t *list);

client_t *client_create(int fd, sockaddr_in_t *addr, char *path, list_t *list);
void client_delete(client_t *client, list_t *list);
void client_close_data(client_t *client);
void client_clear_cmd(client_t *client);

bool client_recv_cmd(client_t *client);
bool client_send(client_t *client, int code, char *msg, size_t len);
void client_accept_pasv(client_t *client);

void client_send_file(client_t *client, char *path);
void client_recv_file(client_t *client, char *path);
void client_send_folder_content(client_t *client, char *path);
void client_send_file_info(client_t *client, char *path);

bool client_check_logged(client_t *client);
void client_set_port_addr(client_t *client, sockaddr_in_t *sockaddr);
bool client_setup_pasv_con(client_t *client, sockaddr_in_t *addr_in);
bool client_connect_to_data(client_t *client);

bool execute_cmd(client_t *client, char *root_path);

bool ip_to_sockaddr(char *str, sockaddr_in_t *sockaddr);
void sockaddr_to_ip(sockaddr_in_t *sockaddr, char buf[24]);
char *make_path(char *cwd, char *path, size_t len);
char *better_realpath(char *ori_path);

bool is_arg_missing(client_t *client, size_t len);
bool check_alloc(client_t *client, void *ptr);
bool is_path_illegal(client_t *client, char *path, char *root_path);
bool is_file_not_valid(client_t *client, char *path, int flags, bool create);
