/**
* Created by saif on 1/18/20.
*/
///

#ifndef MINESPR_PLAY_GAME_H
#define MINESPR_PLAY_GAME_H

#include <stdbool.h>
#include "../boards/board.h"

void play_game();

bool open_cell(cell game_brd[ROWS][COLS],
               cell hidden_brd[ROWS][COLS],
               int mines[][2],
               move mov,
               int *remaining_moves);

void open_ngh(cell game_brd[ROWS][COLS],
              cell hidden_brd[ROWS][COLS],
              move mov,
              int *remaining_moves);

void do_recursion(
        cell game_brd[ROWS][COLS],
        cell hidden_brd[ROWS][COLS],
        move mov,
        int *remaining_moves);

void do_flagging(cell game_brd[ROWS][COLS],
                 cell hidden_brd[ROWS][COLS],
                 int mines[][2],
                 move mov,
                 int *remaining_moves);

bool execute_move(
        cell game_brd[ROWS][COLS],
        cell hidden_brd[ROWS][COLS],
        int mines[][2],
        move mov,
        int *remaining_moves);

#endif //MINESPR_PLAY_GAME_H
