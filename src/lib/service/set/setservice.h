/**
* Created by saif on 2/27/20.
*/
///

#ifndef MINESPR_SETSERVICE_H
#define MINESPR_SETSERVICE_H

void set_row(void);
void set_col(void);
void set_mine(void);
bool set_board(cell game_brd[ROWS][COLS], char *player_file_path);

#endif //MINESPR_SETSERVICE_H
