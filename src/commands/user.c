/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** user
*/

#include <string.h>
#include "ftp.h"

void user_cmd(client_t *client, char *root_path,char *arg, size_t len)
{
    if (arg[0] == 0)
        client_send(client, INVALID_ARG, "Missing parameter.", 18);
    client->username = strdup(arg);
    client_send(client, USERNAME_OK, "User name okay, need password.", 30);
}

void pass_cmd(client_t *client, char *root_path,char *arg, size_t len)
{
    if (client->username == NULL) {
        client_send(client, INVALID_LOGIN, "Missing name.", 13);
    } else if (strlen(client->username) != 9
    || strcmp(client->username, "Anonymous")) {
        client_send(client, INVALID_LOGIN, "Invalid name or password.", 25);
    } else {
        client_send(client, USER_LOGGED, "User logged in, proceed.", 24);
        client->userid = ANONYMOUS_USERID;
    }
}
