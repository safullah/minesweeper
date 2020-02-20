/**
* Created by saif on 2/11/20.
*/
///

#include "player.h"
#include "../validators/validators.h"
#include "../utilities/string_util.h"
#include "../utilities/playing_util.h"
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
    game info;
    info.rows = ROWS;
    info.cols = COLS;
    info.mines = MINES;
    info.aborted = false;
    player p = {NULL, 0, 0, 0, 0, info};
    p.name = get_name();
    return p;
}

bool load_player(cell game_brd[ROWS][COLS]) {
    bool loaded = false;
    char *file_name = concat_filename(PLAYERX);
    DIR *d;
    struct dirent *dir;
    d = opendir("/home/saif/dev/minespr/databank/");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            size_t name_len = strcspn(dir->d_name, "\0");
            char dfile_name[30];
            memset(dfile_name, '\0', sizeof(dfile_name));
            strncpy(dfile_name, dir->d_name, name_len);
            if (strcmp(dfile_name, file_name) == 0) {
                char *file_path = concat_filepath(PLAYERX);
                GAME = fopen(file_path, "r");
                if ((fread(&PLAYERX, sizeof(player), 1, GAME) != 0)) {
                    printf("\nName: %s\n", PLAYERX.name);
                    printf("Games: %d\n", PLAYERX.games);
                    printf("Wins: %d\n", PLAYERX.wins);
                    printf("Losses: %d\n", PLAYERX.losses);
                    printf("Opened cells: %d\n", PLAYERX.cells);
                    if (PLAYERX.info.aborted) {
                        ROWS = PLAYERX.info.rows;
                        COLS = PLAYERX.info.cols;
                        MINES = PLAYERX.info.mines;
                        char *question = "Do you want to load the aborted game? y/n";
                        char *hint = " ";
                        //TODO get_answer();
                        char *answer = get_input(question, hint);
                        bool result = is_answer(answer);
                        if (result && (strcmp(answer, "y") == 0 || strcmp(answer, "yes") == 0)) {
                            for (int i = 0; i < ROWS; ++i) {
                                for (int j = 0; j < COLS; ++j) {
                                    cell c;
                                    if (fread(&c, sizeof(cell), 1, GAME) != 0){
                                        game_brd[i][j] = c;
                                    } else {
                                        printf("Error, loading game board\n");
                                        exit(EXIT_FAILURE);
                                    }
                                }
                            }
                            loaded = true;
                        }
                    }
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
    return loaded;
}

void free_mem(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
