/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** commands
*/

#include <string.h>
#include "ftp.h"
#include "commands.h"

static command_fct_t get_cmd_fct(client_t *client)
{
    for (int i = 0 ; i < NB_COMMANDS; i++) {
        if (client->cmd.size < CMD_LEN[i])
            continue;
        if (!strncmp(CMD_NAME[i], client->cmd.cmd, CMD_LEN[i]))
            return CMD_FCT[i];
    }
    return NULL;
}

static size_t extract_arg(char *buf, char *str)
{
    int i = 0;

    for (; *str != ' ' && !(*str == '\r' && *(str + 1) == '\n'); str++);
    if (*str == '\r')
        return 0;
    str++;
    for (; !(*str == '\r' && *(str + 1) == '\n');
    buf[i] = *str, str++, i++);
    return i;
}

bool execute_cmd(client_t *client, char *root_path)
{
    command_fct_t fct = get_cmd_fct(client);
    char buf[client->cmd.size];
    size_t len;

    if (!fct) {
        client_send(client, INVALID_CMD, "Command not implemented.", 24);
        return false;
    }
    memset(buf, 0, client->cmd.size - 1);
    len = extract_arg(buf, client->cmd.cmd);
    fct(client, root_path, buf, len);
    return true;
}
