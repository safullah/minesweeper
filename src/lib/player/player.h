/** \file player.h
 *  \brief information of player and functions he need
* Created by saif on 2/11/20.
*/
///

#ifndef MINESPR_PLAYER_H
#define MINESPR_PLAYER_H

#include <bits/types/FILE.h>
#include <stdlib.h>
#include "../board/board.h"
/**
 * \GAME
 * \brief a file to save the game
 */

/**
 * \game
 * \brief a struct containing int row, int cols, int mines, bool aborted
 */

/**
 * \player
 * \brief a struct containing char name[50], int games, int wins, int losses, int cells, game info
 */

/**
 * \PLAYERX
 * \brief a global variable of player. Global, because otherwise had to pass it to many func as param
 */
FILE *GAME;

typedef struct {
    int rows;
    int cols;
    int mines;
    bool aborted;
} game;

typedef struct {
    char name[50];
    int games;
    int wins;
    int losses;
    int cells;
    game info;
} player;

player PLAYERX;

char *get_name(void);

player init_player(void);

bool load_player(cell game_brd[ROWS][COLS], char *player_file_path);

bool is_existent(char *db_path, char *player_file);

char *get_answer(char *str);

void free_mem(char **arr, int size);

#endif //MINESPR_PLAYER_H
