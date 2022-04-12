/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** files
*/

#include "ftp.h"

void retr_cmd(client_t *client, char *arg)
{
    if (!client_check_logged(client))
        return;
}

void stor_cmd(client_t *client, char *arg)
{
    if (!client_check_logged(client))
        return;

}

void list_cmd(client_t *client, char *arg)
{
    if (!client_check_logged(client))
        return;
}

void dele_cmd(client_t *client, char *arg)
{
    if (!client_check_logged(client))
        return;
}
