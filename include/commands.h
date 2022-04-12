/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** commands
*/

#pragma once

#define NB_COMMANDS 14

typedef struct client_s client_t;
typedef void (*command_fct_t)(client_t *client, char *arg);

void user_cmd(client_t *client, char *arg);
void pass_cmd(client_t *client, char *arg);
void  cwd_cmd(client_t *client, char *arg);
void cdup_cmd(client_t *client, char *arg);
void quit_cmd(client_t *client, char *arg);
void dele_cmd(client_t *client, char *arg);
void  pwd_cmd(client_t *client, char *arg);
void pasv_cmd(client_t *client, char *arg);
void port_cmd(client_t *client, char *arg);
void help_cmd(client_t *client, char *arg);
void noop_cmd(client_t *client, char *arg);
void retr_cmd(client_t *client, char *arg);
void stor_cmd(client_t *client, char *arg);
void list_cmd(client_t *client, char *arg);

extern const char *CMD_NAME[NB_COMMANDS];
extern const command_fct_t CMD_FCT[NB_COMMANDS];
extern const int CMD_LEN[NB_COMMANDS];
