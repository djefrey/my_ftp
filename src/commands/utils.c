/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** utils
*/

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "ftp.h"

bool is_arg_missing(client_t *client, size_t len)
{
    if (len == 0) {
        client_send(client, 550,
        "Syntax error in parameters or arguments.", 40);
        return true;
    }
    return false;
}

bool check_alloc(client_t *client, void *ptr)
{
    if (ptr == NULL) {
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
        return true;
    }
    return false;
}

bool is_path_illegal(client_t *client, char *path, char *root_path)
{
    int len = strlen(root_path);

    if (strncmp(path, root_path, len)) {
        client_send(client, ILLEGAL_FILE,
        "Requested action not taken. File name not allowed.", 50);
        return true;
    }
    return false;
}

bool is_file_not_valid(client_t *client, char *path, int flags, bool create)
{
    int fd;

    if (create && access(path, F_OK) == -1) {
        fd = open(path, O_CREAT, 0644);
        if (fd == -1) {
            client_send(client, INVALID_FILE,
            "Requested action not taken. File unavailable.", 45);
            return true;
        }
        close(fd);
        return false;
    }
    if (access(path, flags) == -1) {
        client_send(client, INVALID_FILE,
        "Requested action not taken. File unavailable.", 45);
        return true;
    }
    return false;
}
