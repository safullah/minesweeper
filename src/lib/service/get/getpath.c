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

    if (result == NULL) {
        printf("searching for %s...\n", target);
        char *check = strcpy(path, find_dir("/", target));
        if (check == NULL) {
            printf("Error while copying path to databank");
            exit(EXIT_FAILURE);
        } else {
            strcat(path, "/");
        }
    } else {
        strcat(path, "/");
    }
    if (strcmp(path, "") == 0) {
        printf("did not find %s\n", target);
        exit(EXIT_FAILURE);
    }
}
