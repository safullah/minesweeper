/**
* Created by saif on 2/11/20.
*/
///

#ifndef MINESPR_PLAYER_H
#define MINESPR_PLAYER_H

#include <bits/types/FILE.h>
#include <stdlib.h>
#include "../boards/board.h"

FILE *GAME;
typedef struct {
    int rows;
    int cols;
    int mines;
    bool aborted;
} game;

typedef struct {
    char *name;
    int games;
    int wins;
    int losses;
    int cells;
    game info;
} player;

player PLAYERX;
char *get_name();
player init_player();
bool load_player(cell game_brd[ROWS][COLS]);
void load_abortedgame();
void free_mem(char **arr, int size);

#endif //MINESPR_PLAYER_H
