/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_PLAYING_UTIL_H
#define MINESPR_PLAYING_UTIL_H

#include <stdbool.h>
#include "../boards/board.h"
input_of_move separate_str(char str[]);
move get_move(char str[]);
move make_move();

bool play_recursive(
        cell game_brd[ROWS][COLS],
        cell hidden_brd[ROWS][COLS],
        int mines[][2],
        move mov,
        int *remaining_moves);
#endif //MINESPR_PLAYING_UTIL_H
