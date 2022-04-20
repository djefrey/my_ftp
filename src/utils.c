/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** utils
*/

#include <string.h>
#include <stdio.h>
#include "ftp.h"

bool ip_to_sockaddr(char *str, sockaddr_in_t *sockaddr)
{
    unsigned char bytes[6];
    int commas = 0;
    int digits = 0;

    for (; *str; str++) {
        if (*str == ',') {
            commas++;
            digits = 0;
            continue;
        }
        if (commas == 6 || digits == 3 || !(*str >= '0' && *str <= '9'))
            return true;
        bytes[commas] *= 10;
        bytes[commas] += (*str - '0');
        digits++;
    }
    sockaddr->sin_addr.s_addr = *((uint32_t*) bytes);
    sockaddr->sin_port = *((uint16_t*) (bytes + 4));
    return false;
}

void sockaddr_to_ip(sockaddr_in_t *sockaddr, char buf[24])
{
    uint32_t ip = sockaddr->sin_addr.s_addr;
    uint16_t port = sockaddr->sin_port;
    char *ipb = (char*) &ip;
    char *portb = (char*) &port;

    snprintf(buf, 24, "%hhu,%hhu,%hhu,%hhu,%hhu,%hhu",
    ipb[0], ipb[1], ipb[2], ipb[3], portb[0], portb[1]);
}

char *make_path(char *cwd, char *path, size_t len)
{
    int cwd_len = strlen(cwd);
    char buf[cwd_len + len + 2];

    if (path[0] != '/') {
        memcpy(buf, cwd, cwd_len);
        buf[cwd_len] = '/';
        memcpy(cwd_len + buf + 1, path, len);
        buf[cwd_len + len + 1] = 0;
    } else {
        memcpy(buf, path, len);
        buf[len] = 0;
    }
    return better_realpath(buf);
}
