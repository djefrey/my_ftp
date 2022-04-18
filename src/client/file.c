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
    struct stat statbuf;
    int fd;
    char c;

    if (pid == -1) {
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
    } else if (pid == 0) {
        fd = open(path, O_RDONLY);
        if (fd == -1) {
            client_send(client, LOCAL_ERROR,
            "Requested action aborted. Local error in processing.", 52);
            exit(0);
        }
        fstat(fd, &statbuf);
        for (size_t i = 0; i < statbuf.st_size; i++) {
            read(fd, &c, 1);
            write(client->conn.data, &c, 1);
        }
        close(fd);
        exit(0);
    }
}

void client_recv_file(client_t *client, char *path)
{
    pid_t pid = fork();
    fd_set rdset;
    char c;
    int fd;

    if (pid == -1) {
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
    } else if (pid == 0) {
        FD_ZERO(&rdset);
        FD_SET(client->conn.data, &rdset);
        fd = open(path, O_WRONLY | O_CREAT, 0, 644);
        if (fd == -1) {
            client_send(client, LOCAL_ERROR,
            "Requested action aborted. Local error in processing.", 52);
            exit(0);
        }
        while (select(client->conn.data + 1, &rdset, NULL, NULL,
        &(struct timeval) {0, 10}) > 0) {
            read(client->conn.data, &c, 1);
            write(fd, &c, 1);
        }
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
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
    } else if (pid == 0) {
        dir = opendir(path);
        if (!dir) {
            client_send(client, INVALID_FILE,
            "Requested action not taken. File unavailable.", 45);
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
        client_send(client, LOCAL_ERROR,
        "Requested action aborted. Local error in processing.", 52);
    } else if (pid == 0) {
        write(client->conn.data, name, len);
        write(client->conn.data, CRLF, 2);
        exit(0);
    }
}
