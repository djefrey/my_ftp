/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** responses
*/

#pragma once

#define SERV_RDY_IN_MIN 120
#define DATA_CON_OPEN 125
#define FILE_STATUS_OK 150

#define COMMAND_OK 200
#define HELP_MSG 214
#define RDY_FOR_NEW_USER 220
#define CLOSING_CONTROL_CON 221
#define CLOSING_DATA_CON 226
#define PASV_MODE 227
#define USER_LOGGED 230
#define FILE_ACTION_OK 250
#define PATH_CREATED 257

#define USERNAME_OK 331
#define NEED_LOGIN 332

#define DATA_NOT_OPEN 425
#define INVALID_LOGIN 430


#define LOCAL_ERROR 550


#define INVALID_CMD 500
#define INVALID_ARG 501
#define BAD_SEQUENCE 503
#define NOT_LOGGED 530
#define INVALID_FILE 550
#define ILLEGAL_FILE 553
