/**
* Created by saif on 1/10/20.
*/
///

#ifndef MINESPR_BOARD_H
#define MINESPR_BOARD_H

#include "board_variables.h"



void generate_playing_board();
void init_brds(char hidden_brd[ROWS][COLS], char gaming_brd[ROWS][COLS]);
void print_brd(char game_brd[ROWS][COLS]);


#endif //MINESPR_BOARD_H
