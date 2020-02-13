/**
* Created by saif on 2/11/20.
*/
///

#include "player.h"
#include "../validators/validators.h"
#include "../utilities/string_util.h"
#include <stdio.h>
#include <string.h>

char *get_name() {
    char *command = "Enter your name: ";
    char *input = take_input(command);
    char *copy = cutout_bslashn(input);
    return copy;
}

player init_player() {
    player p = {NULL, -1, -1, -1};
    p.name = get_name();
    return p;
}

void free_mem(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
