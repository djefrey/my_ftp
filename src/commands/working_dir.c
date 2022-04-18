/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** path
*/

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include "ftp.h"

void cwd_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    char *path;
    DIR *dir;

    if (!client_check_logged(client) || len == 0)
        return;
    path = make_path(client->cwd, arg, len);
    if (!path)
        return;
    dir = opendir(path);
    if (!dir || !is_valid_path(path, root_path)) {
        free(path);
        return;
    }
    closedir(dir);
    free(client->cwd);
    client->cwd = path;
    client_send(client, FILE_ACTION_OK,
    "Requested file action okay, completed.", 38);
}

void cdup_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    cwd_cmd(client, root_path, "../", 3);
}

void pwd_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    int cwd_len = strlen(client->cwd);
    char buf[cwd_len + 12];

    if (!client_check_logged(client))
        return;
    snprintf(buf, cwd_len + 12, "\"%s\" created.", client->cwd);
    client_send(client, PATH_CREATED, buf, cwd_len + 11);
}
