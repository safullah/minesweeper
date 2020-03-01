/**\file setget.h
 * \brief functions to set values or get values
 *
* Created by saif on 2/27/20.
*/
///

#ifndef MINESPR_GETSERVICE_H
#define MINESPR_GETSERVICE_H

#include "../../board/board.h"
/**\optarg_check
 * \brief is a parameter a cli option and which option it is
 */
typedef struct {
    bool is_option;
    char *option;
} optarg_check;

void get_opt(int argc, char **argv);
optarg_check is_option(char *arg);
void call_set(char *ch);
char *get_path(char *target);
bool load_player(char *player_file_path);
void load_game_info();
void set_row(void);
void set_col(void);
void set_mine(void);
bool set_board(cell game_brd[ROWS][COLS], char *player_file_path);
char *find_dir(char *searchin, char *target);

#endif //MINESPR_GETSERVICE_H
