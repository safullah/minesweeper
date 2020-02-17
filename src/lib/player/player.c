/**
* Created by saif on 2/11/20.
*/
///

#include "player.h"
#include "../validators/validators.h"
#include "../utilities/string_util.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

char *get_name() {
    char *command = "Enter your name: ";
    char *input = take_input(command);
    char *copy = cutout_bslashn(input);
    return copy;
}

player init_player() {
    player p = {NULL, 0, 0, 0, 0};
    p.name = get_name();
    return p;
}

void load_player() {
    char *file_name = concat_filename(PLAYERX);
    DIR *d;
    struct dirent *dir;
    d = opendir("/home/saif/dev/minespr/databank/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            size_t  name_len = strcspn(dir->d_name, "\0");
            char dfile_name[30];
            memset(dfile_name, '\0', sizeof(dfile_name));
            strncpy(dfile_name, dir->d_name, name_len);
            if (strcmp(dfile_name, file_name) == 0) {
                char *file_path = concat_filepath(PLAYERX);
                GAME = fopen(file_path, "r");
                if ((fread(&PLAYERX, sizeof(player), 1, GAME) != 0)) {
                    printf("Name: %s\n", PLAYERX.name);
                    printf("Games: %d\n", PLAYERX.games);
                    printf("Wins: %d\n", PLAYERX.wins);
                    printf("Losses: %d\n", PLAYERX.losses);
                    printf("Opened cells: %d\n", PLAYERX.cells);
                } else {
                    fprintf(stderr, "Error, while loading data!\n");
                    exit(EXIT_FAILURE);
                }
                fclose(GAME);
                break;
            }
        }
        closedir(d);
    }
}

void free_mem(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
