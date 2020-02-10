/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_MINES_UTIL_H
#define MINESPR_MINES_UTIL_H
#include "../boards/board.h"
void place_mines(int mines[][2], cell hidden_brd[ROWS][COLS]);
void count_mines(cell hidden_brd[ROWS][COLS]);
void flag_cell(move mov, cell game_brd[ROWS][COLS], cell hidden_brd[ROWS][COLS]);

#endif //MINESPR_MINES_UTIL_H
