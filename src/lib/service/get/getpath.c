/**
* Created by saif on 2/27/20.
*/
///

#include "getservice.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utilities/string_util.h"

char *get_path(char *target) {
    static char path[PATH_MAX + 1] = {'\0'};
    printf("searching ...\n");
    char *check = strcpy(path, find_dir("/", target));
    if (check == NULL) {
        printf("error, while searhing path of databank\n exiting game ...\n");
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
