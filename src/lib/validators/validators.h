/**
* Created by saif on 1/14/20.
*/
///

#ifndef MINESPR_VALIDATORS_H
#define MINESPR_VALIDATORS_H

#include <stdbool.h>
#include "../playing_board/board.h"
bool isValid(int row, int col);
bool isMine (int row, int col, char board[][MAXSIDE]);
void argc_is_valid(int argc);

#endif //MINESPR_VALIDATORS_H
