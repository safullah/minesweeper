/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_PLAYING_UTIL_H
#define MINESPR_PLAYING_UTIL_H

#include <stdbool.h>
#include "../boards/board.h"
move extract_move(char *str);
char *get_input(char * str, char *hint);
move get_move();
#endif //MINESPR_PLAYING_UTIL_H
