/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** file
*/

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <string.h>
#include "ftp.h"

void client_send_file(client_t *client, char *path)
{
    pid_t pid = fork();
    char buf[1024];
    uint size;
    int fd;

    if (pid == -1) {
        LOCAL_ERROR_SEND(client);
    } else if (pid == 0) {
        fd = open(path, O_RDONLY);
        if (fd == -1) {
            LOCAL_ERROR_SEND(client);
            exit(0);
        }
        while ((size = read(fd, buf, 1024)))
            write(client->conn.data, buf, size);
        close(fd);
        exit(0);
    }
}

void client_recv_file(client_t *client, char *path)
{
    pid_t pid = fork();
    char buf[1024];
    uint size;
    int fd;

    if (pid == -1) {
        LOCAL_ERROR_SEND(client);
    } else if (pid == 0) {
        fd = open(path, O_WRONLY | O_CREAT, 0, 644);
        if (fd == -1) {
            LOCAL_ERROR_SEND(client);
            exit(0);
        }
        while ((size = read(client->conn.data, buf, 1024)))
            write(fd, buf, size);
        close(fd);
        exit(0);
    }
}

void client_send_folder_content(client_t *client, char *path)
{
    pid_t pid = fork();
    DIR *dir;
    struct dirent *content;

    if (pid == -1) {
        LOCAL_ERROR_SEND(client);
    } else if (pid == 0) {
        dir = opendir(path);
        if (!dir) {
            LOCAL_ERROR_SEND(client);
            exit(0);
        }
        while ((content = readdir(dir))) {
            write(client->conn.data, content->d_name, strlen(content->d_name));
            write(client->conn.data, CRLF, 2);
        }
        closedir(dir);
        exit(0);
    }
}

void client_send_file_info(client_t *client, char *path)
{
    char *name = basename(path);
    int len = strlen(name);
    pid_t pid = fork();

    if (pid == -1) {
        LOCAL_ERROR_SEND(client);
    } else if (pid == 0) {
        write(client->conn.data, name, len);
        write(client->conn.data, CRLF, 2);
        exit(0);
    }
}
