/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_PLAYING_UTIL_H
#define MINESPR_PLAYING_UTIL_H

#include <stdbool.h>
#include "../playing_board/board.h"
void makeMove(int *x, int *y);

bool playMinesweeperUtil(
        char myBoard[][MAXSIDE],
        char realBoard[][MAXSIDE],
        int mines[][2],
        int row, int col,
        int *movesLeft);

void playMinesweeper ();

#endif //MINESPR_PLAYING_UTIL_H
