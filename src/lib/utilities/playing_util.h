/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_PLAYING_UTIL_H
#define MINESPR_PLAYING_UTIL_H

#include <stdbool.h>
#include "../playing_board/board.h"
int *retrieve_move(char *str[], int count);
void make_move(int *x_crd, int *y_crd, int row, int col);

bool playMinesweeperUtil(
        char myBoard[][MAXSIDE],
        char realBoard[][MAXSIDE],
        int mines[][2],
        int row, int col,
        int *movesLeft);

void  play_game(int board_rows, int board_cols, int num_of_mines);

#endif //MINESPR_PLAYING_UTIL_H
