/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_VALIDATORS_H
#define MINESPR_VALIDATORS_H

#include <stdbool.h>
#include "../boards/board.h"

bool is_cell_valid(int row, int col);

bool is_mine(int row, int col, cell game_brd[ROWS][COLS]);

bool is_rows_cols_valid();

bool is_mines_valid();

bool is_crd_valid(int row, int col);

bool is_flag(const char *str);

bool is_answer(char *answer);

#endif //MINESPR_VALIDATORS_H
