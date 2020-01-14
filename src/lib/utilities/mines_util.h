/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_MINES_UTIL_H
#define MINESPR_MINES_UTIL_H
#include "../playing_board/board.h"
void placeMines(int mines[][2], char realBoard[][MAXSIDE]);
void replaceMine (int row, int col, char board[][MAXSIDE]);

#endif //MINESPR_MINES_UTIL_H
