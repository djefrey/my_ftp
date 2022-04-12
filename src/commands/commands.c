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
    if (client->cmd.size - 1 < 5)
        return NULL;
    for (int i = 0 ; i < NB_COMMANDS; i++) {
        if (!strncmp(CMD_NAME[i], client->cmd.str, CMD_LEN[i]))
            return CMD_FCT[i];
    }
    return NULL;
}

static void extract_arg(char *buf, char *str, size_t len)
{
    for (; *str != ' ' && !(*str == '\r' && *(str + 1) == '\n'); str++);
    if (*str == '\r')
        return;
    str++;
    for (int i = 0; !(*str == '\r' && *(str + 1) == '\n');
    buf[i] = *str, str++, i++);
}

bool execute_cmd(client_t *client)
{
    command_fct_t fct = get_cmd_fct(client);
    char buf[client->cmd.size];

    if (!fct)
        return false;
    memset(buf, 0, client->cmd.size - 1);
    extract_arg(buf, client->cmd.str, client->cmd.size);
    fct(client, buf);
    return true;
}
