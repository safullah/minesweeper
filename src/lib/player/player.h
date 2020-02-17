/**
* Created by saif on 2/11/20.
*/
///

#ifndef MINESPR_PLAYER_H
#define MINESPR_PLAYER_H

#include <bits/types/FILE.h>
#include <stdlib.h>

FILE *GAME;
typedef struct {
    char *name;
    int games;
    int wins;
    int losses;
    int cells;
} player;

player PLAYERX;
char *get_name();
player init_player();
void load_player();
void free_mem(char **arr, int size);

#endif //MINESPR_PLAYER_H
