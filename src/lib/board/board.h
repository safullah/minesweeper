/** \file board.h
 * \brief
 *
* Created by saif on 1/10/20.
*/
///

#ifndef MINESPR_BOARD_H
#define MINESPR_BOARD_H

#include <stdbool.h>
#include "board_variables.h"

/**
 * \state
 * \brief an enum of three states for a cell
 */

/**
 * \cell
 * \brief cell is a struct with a character \c ch, state \c state and the amount of mines in neighbor cells \c ngh_mines
 */

/**
 * \move
 * \brief move is a struct. There the move of the player is captured
 */
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
    bool abort;
    bool restart;
} move;

void init_brd(cell gaming_brd[ROWS][COLS]);

void print_brd(cell game_brd[ROWS][COLS]);

void print_rmaining_mines(void);

void cheat(cell game_brd[ROWS][COLS]);

#endif //MINESPR_BOARD_H
