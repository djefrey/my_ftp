/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** main
*/

#include <errno.h>
#include <string.h>
#include "ftp.h"

int main(int ac, char **av)
{
    int socket = create_main_socket(atol(av[1]));
    list_t list = NULL;
    char *cmd = NULL;

    if (socket == -1)
        return 84;
    while (true) {
        accept_new_clients(socket, &list);
        for (list_t cpy = list; cpy; cpy = cpy->next) {
            cmd = client_recv(GET(client_t, cpy));
        }
    }
}