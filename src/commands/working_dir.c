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

    if (!client_check_logged(client) || is_arg_missing(client, len))
        return;
    path = make_path(client->cwd, arg, len);
    if (check_alloc(client, path))
        return;
    dir = opendir(path);
    if (!dir || is_path_illegal(client, path, root_path)) {
        client_send(client, INVALID_FILE, "Requested action not taken. File " \
        "unavailable (e.g., file not found, no access).", 79);
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
