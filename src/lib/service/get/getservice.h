/**
* Created by saif on 2/27/20.
*/
///

#ifndef MINESPR_GETSERVICE_H
#define MINESPR_GETSERVICE_H

#include "../../board/board.h"

void *get_opt(int argc, char *argv[]);
char *get_path(char *target);
bool load_player(char *player_file_path);
void load_game_info();


#endif //MINESPR_GETSERVICE_H
