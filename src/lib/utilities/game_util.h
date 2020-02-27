/**
* Created by saif on 1/18/20.
*/
///

#ifndef MINESPR_GAME_UTIL_H
#define MINESPR_GAME_UTIL_H

#include <stdbool.h>
#include "../board/board.h"

void restart_game(cell game_brd[ROWS][COLS], int mines[][2]);

void play_game(char *answer, char *player_file_path);

void save_game(cell game_brd[ROWS][COLS], bool abort);

bool open_cell(cell game_brd[ROWS][COLS], int mines[][2], move mov);

void open_ngh(cell game_brd[ROWS][COLS], move mov);

void flag_cell(cell game_brd[ROWS][COLS], move mov);

bool execute_move(cell game_brd[ROWS][COLS], int mines[][2], move mov);

void open_randomcell(cell game_brd[ROWS][COLS], int mines[][2]);

void help(bool explain_params);

#endif //MINESPR_GAME_UTIL_H
