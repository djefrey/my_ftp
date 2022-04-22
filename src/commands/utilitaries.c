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

static void dele_path(client_t *client, char *path)
{
    if (!remove(path))
        client_send(client, FILE_ACTION_OK,
        "Requested file action okay, completed.", 38);
    else
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
}

void dele_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    char *path;

    if (!client_check_logged(client) || is_arg_missing(client, len))
        return;
    path = make_path(client->cwd, arg, len);
    if (check_alloc(client, path))
        return;
    else if (is_path_illegal(client, path, root_path)
    || is_file_not_valid(client, path, F_OK, false)) {
        free(path);
        return;
    }
    dele_path(client, path);
    free(path);
}
