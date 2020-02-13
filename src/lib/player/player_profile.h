/**
* Created by saif on 2/11/20.
*/
///

#ifndef MINESPR_PLAYER_PROFILE_H
#define MINESPR_PLAYER_PROFILE_H

#include <bits/types/FILE.h>

FILE *GAME;
typedef struct {
    char *name;
    int games;
    int wins;
    int losts;
    int cells;
} player;

char *get_name();
player init_player();
#endif //MINESPR_PLAYER_PROFILE_H
