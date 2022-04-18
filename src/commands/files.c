/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** files
*/

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include "ftp.h"

void retr_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    char *path;

    if (!client_check_logged(client) || is_arg_missing(client, len))
        return;
    path = make_path(client->cwd, arg, len);
    if (check_alloc(client, path) || is_path_illegal(client, path, root_path))
        return;
    if (access(path, R_OK) == -1) {
        client_send(client, INVALID_FILE,
        "Requested action not taken. File unavailable.", 45);
        free(path);
        return;
    }
    if (client->conn.data == -1) {
        client_send(client, DATA_NOT_OPEN, "Can't open data connection.", 27);
        free(path);
        return;
    }
    client_send(client, FILE_STATUS_OK,
    "File status okay; about to open data connection.", 48);
    client_send_file(client, path);
    client_send(client, CLOSING_DATA_CON, "Closing data connection.", 24);
    client_close_data(client);
    free(path);
}

void stor_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    char *path;

    if (!client_check_logged(client))
        return;
    path = make_path(client->cwd, arg, len);
    if (check_alloc(client, path) || is_path_illegal(client, path, root_path))
        return;
    if (access(path, W_OK) == -1 && access(path, F_OK) != -1) {
        client_send(client, INVALID_FILE,
        "Requested action not taken. File unavailable.", 45);
        free(path);
        return;
    }
    client_send(client, FILE_STATUS_OK,
    "File status okay; about to open data connection.", 48);
    client_recv_file(client, path);
    client_send(client, CLOSING_DATA_CON, "Closing data connection.", 24);
    client_close_data(client);
    free(path);
}

void list_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    char *path;
    struct stat statbuf;

    if (!client_check_logged(client))
        return;
    path = len > 0 ? make_path(client->cwd, arg, len) : strdup(client->cwd);
    if (check_alloc(client, path) || is_path_illegal(client, path, root_path))
        return;
    if (stat(path, &statbuf) == -1) {
        client_send(client, INVALID_FILE,
        "Requested action not taken. File unavailable.", 45);
        return;
    }
    if (client->conn.data == -1) {
        client_send(client, DATA_NOT_OPEN, "Can't open data connection.", 27);
        free(path);
        return;
    }
    client_send(client, FILE_STATUS_OK,
    "File status okay; about to open data connection.", 48);
    if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
        client_send_folder_content(client, path);
    else
        client_send_file_info(client, path);
    client_send(client, CLOSING_DATA_CON, "Closing data connection.", 24);
    client_close_data(client);
    free(path);
}

void dele_cmd(client_t *client, char *root_path, char *arg, size_t len)
{
    char *path;

    if (!client_check_logged(client) || is_arg_missing(client, len))
        return;
    path = make_path(client->cwd, arg, len);
    if (check_alloc(client, path) || is_path_illegal(client, path, root_path))
        return;
    if (access(path, F_OK) == -1) {
        client_send(client, INVALID_FILE,
        "Requested action not taken. File unavailable.", 45);
        free(path);
        return;
    }
    if (!remove(path))
        client_send(client, FILE_ACTION_OK,
        "Requested file action okay, completed.", 38);
    else
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
    free(path);
}
