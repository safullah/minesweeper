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

char *concat_filepath(player p) {
    static char filepath[PATH_MAX] = {'\0'};
    char *path = find_dir("/", "minespr_databank");
    if (path) {
        strcpy(filepath, path);
        strcat(filepath, "/");
        strcat(filepath, p.name);
        strcat(filepath, ".txt");
        return filepath;
    } else {
        printf("Error, while opening databank");
        exit(EXIT_FAILURE);
    }

}

char *find_dir(char *searchin, char *searchfor) {
    static char path[PATH_MAX] = {'\0'};
    DIR *directory;
    struct dirent *entry;
    struct stat statbuf;

    if ((directory = opendir(searchin)) != NULL) {
        int cwd = open(".", O_RDONLY);
        chdir(searchin);
        while ((entry = readdir(directory)) != NULL) {
            lstat(entry->d_name, &statbuf);
            if (S_ISDIR(statbuf.st_mode)) {
                // Found a directory, but ignore . and ..
                if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
                    continue;
                }
                if (strcmp(entry->d_name, searchfor) == 0) {
                    if (realpath("./minespr_databank", path) != NULL) {
                        return path;
                    } else {
                        perror("realpath() error");
                        exit(EXIT_FAILURE);
                    }
                }
                // Recurse at a new indent level
                find_dir(entry->d_name, searchfor);
            }
        }
        fchdir(cwd);
        close(cwd);
        closedir(directory);
    }
    return path;
}

void clear_overflow() {
    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        //do nothing until buffer is cleared
    }
}

