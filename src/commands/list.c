/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** commands
*/

#include "commands.h"

const char *CMD_NAME[NB_COMMANDS] = {
    "USER",
    "PASS",
    "CWD",
    "CDUP",
    "QUIT",
    "DELE",
    "PWD",
    "PASV",
    "PORT",
    "HELP",
    "NOOP",
    "RETR",
    "STOR",
    "LIST",
};

const command_fct_t CMD_FCT[NB_COMMANDS] = {
    user_cmd,
    pass_cmd,
    cwd_cmd,
    cdup_cmd,
    quit_cmd,
    dele_cmd,
    pwd_cmd,
    pasv_cmd,
    port_cmd,
    help_cmd,
    noop_cmd,
    retr_cmd,
    stor_cmd,
    list_cmd,
};

const int CMD_LEN[NB_COMMANDS] = {
    4,
    4,
    3,
    4,
    4,
    4,
    3,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
};
