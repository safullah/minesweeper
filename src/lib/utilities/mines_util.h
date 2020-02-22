/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_MINES_UTIL_H
#define MINESPR_MINES_UTIL_H
#include "../board/board.h"

void place_mines(int mines[][2], cell hidden_brd[ROWS][COLS]);
void count_mines(cell game_brd[ROWS][COLS]);

#endif //MINESPR_MINES_UTIL_H
