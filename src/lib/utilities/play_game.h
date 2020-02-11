/**
* Created by saif on 1/18/20.
*/
///

#ifndef MINESPR_PLAY_GAME_H
#define MINESPR_PLAY_GAME_H

#include <stdbool.h>
#include "../boards/board.h"

void restart_game(cell game_brd[ROWS][COLS],
                  cell hidden_brd[ROWS][COLS],
                  int mines[][2]);
void play_game(bool restart);

bool open_cell(cell game_brd[ROWS][COLS],
               cell hidden_brd[ROWS][COLS],
               int mines[][2],
               move mov);

void open_ngh(cell game_brd[ROWS][COLS],
              cell hidden_brd[ROWS][COLS],
              move mov);

void do_recursion(
        cell game_brd[ROWS][COLS],
        cell hidden_brd[ROWS][COLS],
        move mov);

void do_flagging(cell game_brd[ROWS][COLS],
                 cell hidden_brd[ROWS][COLS],
                 int mines[][2],
                 move mov);

bool execute_move(
        cell game_brd[ROWS][COLS],
        cell hidden_brd[ROWS][COLS],
        int mines[][2],
        move mov);

#endif //MINESPR_PLAY_GAME_H
