/**
* Created by saif on 2/11/20.
*/
///

#ifndef MINESPR_PLAYER_H
#define MINESPR_PLAYER_H

#include <bits/types/FILE.h>
#include <stdlib.h>
#include "../board/board.h"

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

char *get_name();

player init_player();

bool load_player(cell game_brd[ROWS][COLS], char *db_path);

bool is_existent(char *db_path);

char *get_answer(char *str);

void load_abortedgame();

void free_mem(char **arr, int size);

#endif //MINESPR_PLAYER_H
