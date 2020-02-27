/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_VALIDATORS_H
#define MINESPR_VALIDATORS_H

#include <stdbool.h>
#include "../board/board.h"

bool is_cell_valid(int row, int col);

bool is_mine(int row, int col, cell game_brd[ROWS][COLS]);

bool is_row_valid(int row, char *error);

bool is_col_valid(int col, char *error);

bool is_mine_valid(int mine, char *error);

bool is_crd_valid(int col, int row);

bool is_flag(const char *str);

bool is_answer(char *answer);

#endif //MINESPR_VALIDATORS_H
