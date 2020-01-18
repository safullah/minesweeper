/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_VALIDATORS_H
#define MINESPR_VALIDATORS_H

#include <stdbool.h>
#include "../playing_board/board.h"
bool is_cell_valid(int row, int col);
bool is_mine (int row, int col, char **board);
void is_argc_valid(int argc);
void is_rows_cols_valid(int rows, int cols);
void is_mines_valid(int mines, int rows, int cols);
bool is_coordinate_valid(int x_crd, int y_crd, int rows, int cols);
#endif //MINESPR_VALIDATORS_H
