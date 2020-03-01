/** \file getpath.c
 * \brief gets the path of a file
* Created by saif on 2/27/20.
*/
///

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "setget.h"

/**
 * \brief gets the path of \c target
 * Searches \c target from root
 *
 * @param target    the file or directory which is searched for
 * @return char *   return the absolute path
 */
char *get_path(char *target) {
    static char path[PATH_MAX + 1] = {'\0'};
    printf("searching ...\n");
    char *check = strcpy(path, find_dir("/", target));
    if (check == NULL) {
        printf("Error, while searching for %s \n exiting game ...\n", target);
        exit(EXIT_FAILURE);
    } else {
        strcat(path, "/");
    }

    if (strcmp(path, "") == 0) {
        printf("did not find %s\n exiting game ...", target);
        exit(EXIT_FAILURE);
    } else {
        return path;
    }
}

/**
 * \brief searches target in searchin
 *
 * Searches through \c searchin and in all it subdirectories for \c target
 * @param searchin
 * @param target
 * @return char *       return the absolute path of \c target
 */
char *find_dir(char *searchin, char *target) {
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
                    if (strcmp(entry->d_name, target) == 0) {
                        if (realpath(target, path) != NULL) {
                            break;
                        } else {
                            perror("realpath() error");
                            exit(EXIT_FAILURE);
                        }
                    }
                    // Recurse this directory
                    find_dir(entry->d_name, target);
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
