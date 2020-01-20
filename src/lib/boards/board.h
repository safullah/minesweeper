/**
* Created by saif on 1/10/20.
*/
///

#ifndef MINESPR_BOARD_H
#define MINESPR_BOARD_H

#include <stdbool.h>
#include "board_variables.h"
typedef enum {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z} alphabet;
typedef enum {hidden, opened, flagged} state;

typedef struct{
    char ch;
    state s;
    int ngh_mines;
} cell;

typedef struct {
    char alpha;
    char num[2];
} input_of_move;

typedef struct {
    bool flag;
    char col;
    int row;
} move;
void  init_brds(cell hidden_brd[ROWS][COLS], cell gaming_brd[ROWS][COLS]);
void print_brd(cell game_brd[ROWS][COLS]);

#endif //MINESPR_BOARD_H
