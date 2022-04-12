/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** path
*/

#include "ftp.h"

void cwd_cmd(client_t *client, char *arg)
{
    if (!client_check_logged(client))
        return;
}

void cdup_cmd(client_t *client, char *arg)
{
    if (!client_check_logged(client))
        return;
}

void pwd_cmd(client_t *client, char *arg)
{
    if (!client_check_logged(client))
        return;
}
