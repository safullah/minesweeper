/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_VALIDATORS_H
#define MINESPR_VALIDATORS_H

#include <stdbool.h>
#include "../boards/board.h"

bool is_cell_valid(int row, int col);

bool is_mine(int row, int col, cell board[ROWS][COLS]);

void is_argc_valid(int argc);

void is_rows_cols_valid();

void is_mines_valid();

bool is_crd_valid(int x_crd, int y_crd);

bool is_flag(char str[]);

bool is_overflow();

bool is_answer(char *answer);

#endif //MINESPR_VALIDATORS_H
