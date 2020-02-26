/** \file
 *  \brief player.c
* Created by saif on 2/11/20.
*/
///

#include "player.h"
#include "../validators/validators.h"
#include "../utilities/playing_util.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/**
 * \brief gets the name of the player when starting the game
 *
 * with the function \c get_input() the name is retrieved
 * max length of name is set to 50 chars
 *
 * @return char * name
 */
char *get_name(void) {
    char *command = "Enter your <name>";
    char *hint = command;
    char *input = get_input(command, hint);
    return input;
}

/**
 * \brief initializes a player when starting the game
 *
 * Information of game \c info are set such as rows and cols of game board, the amount of mines and if the game is aborted
 * player \c p is initialized  via \c get_name() the name is set
 *
 * @return player
 */
player init_player(void) {
    game info;
    info.rows = ROWS;
    info.cols = COLS;
    info.mines = MINES;
    info.aborted = false;
    player p = {"\0", 0, 0, 0, 0, info};
    strcpy(p.name, get_name());
    return p;
}

/**
 * \brief loads an existent player
 *
 * load_player loads the data of a player
 * his name, played games, wins, losses and opened cells in total are displayed
 * if the player had an aborted game he is asked if he wants to continue the aborted game
 * if yes the aborted game is loaded
 *
 * @param game_brd              the game board is set the value of the aborted game, f player wishes to continue the aborted game
 * @param player_file_path      path to the file of player
 *
 * @return boolean      existent player loaded or not
 */
bool load_player(cell game_brd[ROWS][COLS], char *player_file_path) {
    bool loaded = false;
    GAME = fopen(player_file_path, "r");
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
                            printf("Error, while loading the game\n");
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
/**
 * \brief is player in databank
 *
 * \c searches the databank for \c player_file
 *
 * @param db_path       path to databank
 * @param player_file   name of the players file
 * @return boolean      does the player exist in databank or nor
 */
bool is_existent(char *db_path, char *player_file) {
    bool exists = false;
    DIR *databank;
    struct dirent *dir;
    if ((databank = opendir(db_path)) == NULL) {
        printf("Error, cannot open directory: %s\n", db_path);
        exit(EXIT_FAILURE);
    }
    if (databank) {
        while ((dir = readdir(databank)) != NULL) {
            size_t name_len = strcspn(dir->d_name, "\0");
            char file_name[50];
            memset(file_name, '\0', sizeof(file_name));
            strncpy(file_name, dir->d_name, name_len);
            if (strcmp(file_name, player_file) == 0) {
                exists = true;
                break;
            }
        }
    }
    closedir(databank);
    return exists;

}

/**
 * \brief gets the answer to the question Load the aborted game? y/n
 *
 * The player can type yes, no or y,n
 * capital letter and small letter are both accepted
 *
 * @param str       this the question the player is being asked for
 * @return char *answer     y or n
 */
char *get_answer(char *str) {
    bool is_correct = false;
    char *answer = "\0";
    while (!is_correct) {
        answer = get_input(str, str);
        is_correct = is_answer(answer);
    }
    return answer;
}

//TODO delete in case I don't need it
void free_mem(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
