/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** commands
*/

#pragma once

#include <stddef.h>

#define NB_COMMANDS 14

typedef struct client_s client_t;
typedef void (*command_fct_t)(client_t *client,
char *root_path, char *arg, size_t len);

void user_cmd(client_t *client, char *root_path, char *arg, size_t len);
void pass_cmd(client_t *client, char *root_path, char *arg, size_t len);
void  cwd_cmd(client_t *client, char *root_path, char *arg, size_t len);
void cdup_cmd(client_t *client, char *root_path, char *arg, size_t len);
void quit_cmd(client_t *client, char *root_path, char *arg, size_t len);
void dele_cmd(client_t *client, char *root_path, char *arg, size_t len);
void  pwd_cmd(client_t *client, char *root_path, char *arg, size_t len);
void pasv_cmd(client_t *client, char *root_path, char *arg, size_t len);
void port_cmd(client_t *client, char *root_path, char *arg, size_t len);
void help_cmd(client_t *client, char *root_path, char *arg, size_t len);
void noop_cmd(client_t *client, char *root_path, char *arg, size_t len);
void retr_cmd(client_t *client, char *root_path, char *arg, size_t len);
void stor_cmd(client_t *client, char *root_path, char *arg, size_t len);
void list_cmd(client_t *client, char *root_path, char *arg, size_t len);

extern const char *CMD_NAME[NB_COMMANDS];
extern const command_fct_t CMD_FCT[NB_COMMANDS];
extern const int CMD_LEN[NB_COMMANDS];
