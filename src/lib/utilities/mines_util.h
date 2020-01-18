/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_MINES_UTIL_H
#define MINESPR_MINES_UTIL_H
#include "../playing_board/board.h"
void place_mines(int **mines, char **realBoard);
void replaceMine (int row, int col, char board[][MAXSIDE]);

#endif //MINESPR_MINES_UTIL_H
