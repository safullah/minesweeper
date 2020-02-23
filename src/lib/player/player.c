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
    char *command = "Enter your <name>";
    char *hint = command;
    char *input = get_input(command, hint);
    return input;
}

player init_player() {
    game info;
    info.rows = ROWS;
    info.cols = COLS;
    info.mines = MINES;
    info.aborted = false;
    player p = {"\0", 0, 0, 0, 0, info};
    strcpy(p.name, get_name());
    return p;
}

bool load_player(cell game_brd[ROWS][COLS]) {
    bool loaded = false;
    char *file_path = concat_filepath(PLAYERX);
    GAME = fopen(file_path, "r");
    if ((fread(&PLAYERX, sizeof(player), 1, GAME) != 0)) {
        printf("Name: %s\n", PLAYERX.name);
        printf("Games: %d\n", PLAYERX.games);
        printf("Wins: %d\n", PLAYERX.wins);
        printf("Losses: %d\n", PLAYERX.losses);
        printf("Opened cells: %d\n", PLAYERX.cells);
        if (PLAYERX.info.aborted) {
            ROWS = PLAYERX.info.rows;
            COLS = PLAYERX.info.cols;
            MINES = PLAYERX.info.mines;
            char *question = "Load the aborted game? y/n";
            char *answer = get_answer(question);
            if ((strcmp(answer, "y") == 0 || strcmp(answer, "yes") == 0)) {
                for (int i = 0; i < ROWS; ++i) {
                    for (int j = 0; j < COLS; ++j) {
                        cell c;
                        if (fread(&c, sizeof(cell), 1, GAME) == 1) {
                            game_brd[i][j] = c;
                        } else {
                            printf("Error, loading the game\n");
                            fclose(GAME);
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                loaded = true;
            }
        }
    } else {
        printf("Error, while loading player!\n");
        fclose(GAME);
        exit(EXIT_FAILURE);
    }
    fclose(GAME);
    return loaded;
}

bool is_existent() {
    bool exists = false;
    char *players_file = concat_filename(PLAYERX);
    DIR *databank;
    struct dirent *dir;
    static char dbpath[PATH_MAX] = {'\0'};
    char *path = find_dir("/", "minespr_databank");
    if (path) {
        strcpy(dbpath, path);
        strcat(dbpath, "/");
        if ((databank = opendir(dbpath)) == NULL) {
            printf("Error, cannot open directory: %s\n", dbpath);
            exit(EXIT_FAILURE);
        }
        if (databank) {
            while ((dir = readdir(databank)) != NULL) {
                size_t name_len = strcspn(dir->d_name, "\0");
                char file_name[50];
                memset(file_name, '\0', sizeof(file_name));
                strncpy(file_name, dir->d_name, name_len);
                if (strcmp(file_name, players_file) == 0) {
                    exists = true;
                    break;
                }
            }
        }
        closedir(databank);
        return exists;
    } else {
        printf("Error, while opening databank");
        exit(EXIT_FAILURE);
    }

}

char *get_answer(char *str) {
    bool is_correct = false;
    char *answer = "\0";
    while (!is_correct) {
        answer = get_input(str, str);
        is_correct = is_answer(answer);
    }
    return answer;
}

void free_mem(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
