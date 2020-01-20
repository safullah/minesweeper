/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_PLAYING_UTIL_H
#define MINESPR_PLAYING_UTIL_H

#include <stdbool.h>
#include "../boards/board.h"
int *get_move(char str[], int count);
int *make_move();

bool play_recursive(
        cell game_brd[ROWS][COLS],
        cell hidden_brd[ROWS][COLS],
        int mines[][2],
        int x_crd, int y_crd,
        int *remaining_moves);
#endif //MINESPR_PLAYING_UTIL_H
