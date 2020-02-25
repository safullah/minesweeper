/**
* Created by saif on 2/12/20.
*/
///

#include "string_util.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

char *get_input(char *str, char *hint) {
    printf("%s ", str);
    char input[50];
    memset(input, '\0', sizeof(char) * 50);
    char *result = NULL;
    while (result == NULL || strcmp(result, "\n") == 0) {
        result = fgets(input, sizeof(input) / sizeof(char), stdin);
        if (strchr(input, '\n') == NULL) {
            printf("input too long: %s\n", result);
            printf("\n%s ", hint);
            clear_overflow();
            result = NULL;
        }
    }
    char *copy = cutout_backslashn(input);
    return copy;
}

char *cutout_backslashn(const char *str) {
    static char copy[50];
    memset(copy, '\0', sizeof(char) * 50);
    for (int j = 0; *(str + j) != '\n'; j++) {
        copy[j] = *(str + j);
    }
    return copy;
}

char *concat_filename(player p) {
    static char file_name[50];
    memset(file_name, '\0', sizeof(file_name));
    strcpy(file_name, p.name);
    strcat(file_name, ".txt");
    return file_name;
}

char *concat_filepath(player p, char *db_path) {
    static char filepath[PATH_MAX+1] = {'\0'};
    strcpy(filepath, db_path);
    strcat(filepath, "/");
    strcat(filepath, p.name);
    strcat(filepath, ".txt");
    return filepath;
}

char *find_dir(char *searchin, char *searchfor) {
    //TODO check if searchfor is in the current or down
    // ./searchfor existent in the current or in any folder down
    // if not look above ../searchfor existent
    // else search from root

    static char path[PATH_MAX+1] = {'\0'};
    DIR *directory;
    struct dirent *entry;
    struct stat statbuf;
    if ((directory = opendir(searchin)) != NULL) {
        int cwd = open(".", O_RDONLY);
        chdir(searchin);
        while ((entry = readdir(directory)) != NULL && (strcmp(path, "") == 0)) {
            errno = 0;
            if (lstat(entry->d_name, &statbuf) == 0) {
                if (S_ISDIR(statbuf.st_mode)) {
                    // Found a directory, but ignore . and ..
                    if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
                        continue;
                    }
                    if (strcmp(entry->d_name, searchfor) == 0) {
                        if (realpath(searchfor, path) != NULL) {
                            break;
                        } else {
                            perror("realpath() error");
                            exit(EXIT_FAILURE);
                        }
                    }
                    // Recurse this directory
                    find_dir(entry->d_name, searchfor);
                }
            }
        }
        fchdir(cwd);
        close(cwd);
        if (closedir(directory) == -1) {
            perror("closedir() error");
            exit(EXIT_FAILURE);
        }
    }
    return path;
}

void clear_overflow() {
    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        //do nothing until buffer is cleared
    }
}

