/*
** EPITECH PROJECT, 2022
** B-NWP-400-STG-4-1-myftp-jeffrey.winkler
** File description:
** path
*/

#include <stdio.h>
#include <string.h>
#include <sys/param.h>

static void handle_special_dir(char *path, int *i, int prev_folder)
{
    if (!strncmp(path + *i, "//", 2))
        memmove(path + *i, path + *i + 1, strlen(path + *i + 1) + 1);
    if (!strncmp(path + *i, "/./", 3)) {
        memmove(path + *i, path + *i + 2, strlen(path + *i + 2) + 1);
        *i = 0;
    }
    i = i;
    if (!strncmp(path + *i, "/../", 4) || !strncmp(path + *i, "/..\0", 4)) {
        memmove(path + prev_folder, path + *i + 3, strlen(path + *i + 3) + 1);
        *i = 0;
    }
}

char *better_realpath(char *ori_path)
{
    char path[PATH_MAX];
    char prev_folder = 0;

    if (strlen(ori_path) >= PATH_MAX)
        return NULL;
    memset(path, 0, PATH_MAX);
    strcpy(path, ori_path);
    for (int i = 0; path[i]; i++) {
        if (path[i] != '/')
            continue;
        handle_special_dir(path, &i, prev_folder);
        prev_folder = i;
    }
    return strdup(path);
}
