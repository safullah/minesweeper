/**
 * \file playing_util.c
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_PLAYING_UTIL_H
#define MINESPR_PLAYING_UTIL_H

#include <stdbool.h>
#include "../board/board.h"

move extract_move(char *str);
move get_move(void);

#endif //MINESPR_PLAYING_UTIL_H
