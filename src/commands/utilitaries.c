/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** utils
*/

#include "ftp.h"

void noop_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    client_send(client, COMMAND_OK, "Command ok.", 11);
}


void help_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    client_send(client, HELP_MSG, "HELP !", 6);
}
