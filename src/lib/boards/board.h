/**
* Created by saif on 1/10/20.
*/
///

#ifndef MINESPR_BOARD_H
#define MINESPR_BOARD_H

#include <stdbool.h>
#include "board_variables.h"

typedef enum {
    hidden, opened, flagged
} state;

typedef struct {
    char ch;
    state state;
    int ngh_mines;
} cell;

typedef struct {
    bool flag;
    int col;
    int row;
} move;

void init_brd(cell gaming_brd[ROWS][COLS]);

void print_brd(cell game_brd[ROWS][COLS]);

void print_rmaining_mines();

void print_mbrd(cell hidden_brd[ROWS][COLS]);

#endif //MINESPR_BOARD_H
