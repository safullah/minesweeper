/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_MINES_UTIL_H
#define MINESPR_MINES_UTIL_H
#include "../boards/board.h"
void place_mines(int mines[][2], char hidden_brd[ROWS][COLS]);
void replace_mine (int row, int col, char board[ROWS][COLS]);

#endif //MINESPR_MINES_UTIL_H
