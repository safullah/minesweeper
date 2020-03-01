/**
* Created by saif on 2/27/20.
*/
///

#ifndef MINESPR_GETSERVICE_H
#define MINESPR_GETSERVICE_H

#include "../../board/board.h"

typedef struct {
    bool is_option;
    char *option;
} optarg_check;

void get__opt(int argc, char *argv[]);
optarg_check is_option(char *arg);
void call_set(char *ch);
char *get_path(char *target);
bool load_player(char *player_file_path);
void load_game_info();

#endif //MINESPR_GETSERVICE_H
